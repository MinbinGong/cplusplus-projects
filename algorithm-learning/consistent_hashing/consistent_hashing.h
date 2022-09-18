// In consistent hashing, a ring is represented as an array of sorted in ascending order tokens,
// and each of those tokens identifies a segment in the ring
//
// The key property is that every segment owns the ring-space defined by the range:
// [prev_segment.token, segment.token], that is, starting but excluding the token of the previous
// segment in the ring, upto and including the token of the segment
//
// The two exceptions are for tokens that <= the first tokens in the ring or > last tokens in the
// ring (ring semantics)
// -- For the last segment in the array, its next segment is the first segment in the array
// -- For the first segment in the array, its previous segment is the last segment in the array
//
//
// You should operate on ring segments, and for a typical distributed service, each segment will
// be owned by a primary replica, and based on replication strategies and factors, more (usually,
// the successor) segments will also get to hold the same segment's data.

#pragma once
#ifdef HAVE_SWITCH
#include "switch.h"
#include "switch_vector.h"
#include <experimental/optional>
#else
#include <algorithm>
#include <experimental/optional>
#include 