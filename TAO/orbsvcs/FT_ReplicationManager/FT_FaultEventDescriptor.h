/* -*- C++ -*- */
//=============================================================================
/**
 *  @file    FT_FaultEventDescriptor.h
 *
 *  $Id$
 *
 *  This file is part of TAO's implementation of Fault Tolerant CORBA.
 *
 *  @author Steve Totten <totten_s@ociweb.com>
 */
//=============================================================================


#ifndef FT_FAULT_EVENT_DESCRIPTOR_H_
#define FT_FAULT_EVENT_DESCRIPTOR_H_

#include /**/ "ace/pre.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "orbsvcs/FT_CORBAC.h"
#include "orbsvcs/PortableGroupC.h"

namespace TAO
{
  /// Helper class for describing the properties in a fault event.
  struct FT_FaultEventDescriptor
  {
  public:

    /// Default constructor.
    FT_FaultEventDescriptor ();

    ////////
    /// Data members.

    /// Flags indicating the "extent" of the fault.
    int all_at_location_failed;
    int all_of_type_at_location_failed;
    int object_at_location_failed;
    int object_is_primary;

    /// The location of the fault.
    FT::Location_var location;

    /// The TypeId of the object that faulted.
    FT::TypeId_var type_id;

    /// The ObjectGroupId of the faulted object.
    PortableGroup::ObjectGroupId object_group_id;

    /// Other properties of the object group to which the fault relates.
    FT::MembershipStyleValue membership_style;
    FT::ReplicationStyleValue replication_style;
    FT::MinimumNumberReplicasValue minimum_number_replicas;
    FT::InitialNumberReplicasValue initial_number_replicas;

  };

} // namespace TAO

#include /**/ "ace/post.h"

#endif  /* FT_FAULT_EVENT_DESCRIPTOR_H_ */

