// This may look like C, but it's really -*- C++ -*-
// $Id$

// ============================================================================
//
// = LIBRARY
//    TAO
//
// = FILENAME
//   IIOP_Connect.h
//
// = AUTHOR
//   Chris Cleeland
//
// ============================================================================

#ifndef TAO_IIOP_CONNECT_H
#define TAO_IIOP_CONNECT_H

#include "ace/Reactor.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/Acceptor.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/Synch.h"
#include "ace/Svc_Handler.h"

#include "tao/corbafwd.h"
#include "tao/Wait_Strategy.h"

#include "tao/IIOP_Transport.h"

// Forward Decls
class TAO_ORB_Core;
class TAO_ORB_Core_TSS_Resources;


typedef ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH>
        TAO_SVC_HANDLER;

// ****************************************************************

class TAO_IIOP_Handler_Base : public TAO_SVC_HANDLER
{
public:
  TAO_IIOP_Handler_Base (ACE_Thread_Manager *t);
  TAO_IIOP_Handler_Base (TAO_ORB_Core *orb_core);

  virtual TAO_Transport *transport (void) = 0;
};

class TAO_Export TAO_IIOP_Client_Connection_Handler : public TAO_IIOP_Handler_Base
{
  // = TITLE
  //      <Svc_Handler> used on the client side and returned by the
  //      <TAO_CONNECTOR>.
public:
  // = Intialization method.
  TAO_IIOP_Client_Connection_Handler (ACE_Thread_Manager *t = 0,
                                      TAO_ORB_Core* orb_core = 0);

  virtual ~TAO_IIOP_Client_Connection_Handler (void);

  // = <Connector> hook.
  virtual int open (void *);
  // Activation template method.

  // = Event Handler overloads

  virtual int handle_input (ACE_HANDLE = ACE_INVALID_HANDLE);
  // Called when a a response from a twoway invocation is available.

  virtual int handle_close (ACE_HANDLE = ACE_INVALID_HANDLE,
                            ACE_Reactor_Mask = ACE_Event_Handler::NULL_MASK);
  // Perform appropriate closing.

  virtual int close (u_long flags = 0);
  // Object termination hook.

  virtual TAO_Transport *transport (void);
  // Return the transport objects

protected:
  TAO_IIOP_Client_Transport transport_;
  // Reference to the transport object, it is owned by this class.

  TAO_ORB_Core *orb_core_;
  // Cached ORB Core.
};

// ****************************************************************

class TAO_Export TAO_IIOP_Server_Connection_Handler : public TAO_IIOP_Handler_Base
{
  // = TITLE
  //   Handles requests on a single connection in a server.

public:
  TAO_IIOP_Server_Connection_Handler (ACE_Thread_Manager* t = 0);
  TAO_IIOP_Server_Connection_Handler (TAO_ORB_Core *orb_core);
  ~TAO_IIOP_Server_Connection_Handler (void);
  // Constructor.

  virtual int open (void *);
  // Called by the <Strategy_Acceptor> when the handler is completely
  // connected.  Argument is unused.

  // = Active object activation method.
  virtual int activate (long flags = THR_NEW_LWP,
                        int n_threads = 1,
                        int force_active = 0,
                        long priority = ACE_DEFAULT_THREAD_PRIORITY,
                        int grp_id = -1,
                        ACE_Task_Base *task = 0,
                        ACE_hthread_t thread_handles[] = 0,
                        void *stack[] = 0,
                        size_t stack_size[] = 0,
                        ACE_thread_t  thread_names[] = 0);

  virtual int svc (void);
  // Only used when the handler is turned into an active object by
  // calling <activate>.  This serves as the event loop in such cases.

  // = Template Methods Called by <handle_input>

  TAO_Transport *transport (void);

protected:

  // = Event Handler overloads

  virtual int handle_input (ACE_HANDLE = ACE_INVALID_HANDLE);
  // Reads a message from the <peer()>, dispatching and servicing it
  // appropriately.

  virtual int handle_close (ACE_HANDLE = ACE_INVALID_HANDLE,
                            ACE_Reactor_Mask = ACE_Event_Handler::NULL_MASK);
  // Perform appropriate closing.

protected:
  TAO_IIOP_Server_Transport transport_;
  // @@ New transport object reference.

  TAO_ORB_Core *orb_core_;
  // Cached ORB Core.

  TAO_ORB_Core_TSS_Resources *tss_resources_;
  // Cached tss resources of the ORB that activated this object.
};

#if defined (__ACE_INLINE__)
#include "tao/IIOP_Connect.i"
#endif /* __ACE_INLINE__ */

#endif /* TAO_IIOP_CONNECT_H */
