//
// Copyright (C) 2013 OpenSim Ltd.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#ifndef __INET_IRECEIVER_H_
#define __INET_IRECEIVER_H_

#include "IListening.h"
#include "INoise.h"
#include "IReception.h"
#include "IListeningDecision.h"
#include "IReceptionDecision.h"
#include "RadioControlInfo_m.h"

namespace inet {

namespace physicallayer
{

/**
 * This interface represents a physical device (a part of the radio) which converts
 * electric signals into packets.
 *
 * The receiver interface supports optimistic parallel computation of reception
 * results. For this reason some functions are marked to be purely functional.
 * They must be qualified with const and all of their parameters must also be
 * qualified with const. Moreover they are forbidden to access any state that
 * can change over time to avoid non-deterministic behavior. These functions may
 * be called from background threads running parallel with the main simulation
 * thread. They may also be called several times due to cache invalidation before
 * the actual result is needed. This process is controlled by the radio medium.
 */
// TODO: this is rather an interface for receivers that support "what if" questions for the future (parallel computation)
// TODO: the reception API must be purely functional enforced by the compiler (unfortunately this is impossible in C++)
// TODO: so we need to be very careful, because it's pretty easy to break the purely function API just be reading a non-const member
// TODO: it's probably better to split this interface and all other interfaces into two, one with state that changes over time
// TDOO: and another with purely function API qualified with const functions and members variables
class INET_API IReceiver : public IPrintableObject
{
    public:
        /**
         * Returns the minimum interference power below which receptions are to
         * be ignored while computing the interference. Returns a value in the
         * range [0, +infinity) or NaN if unspecified.
         */
        virtual W getMinInterferencePower() const = 0;

        /**
         * Returns the minimum reception power below which successful reception
         * is definitely not possible. Returns a value in the range [0, +infinity)
         * or NaN if unspecified.
         */
        virtual W getMinReceptionPower() const = 0;

        /**
         * Returns a description of how the receiver is listening on the radio medium.
         */
        virtual const IListening *createListening(const IRadio *radio, const simtime_t startTime, const simtime_t endTime, const Coord startPosition, const Coord endPosition) const = 0;

        /**
         * Returns the result of the listening process specifying the reception
         * state of the receiver. This function must be purely functional and
         * support optimistic parallel computation.
         */
        virtual const IListeningDecision *computeListeningDecision(const IListening *listening, const std::vector<const IReception *> *interferingReceptions, const INoise *backgroundNoise) const = 0;

        /**
         * Returns whether the transmission can be received successfully or not.
         * This function need not be purely functional and need not support
         * optimistic parallel computation.
         */
        virtual bool computeIsReceptionPossible(const ITransmission *transmission) const = 0;

        /**
         * Returns whether the transmission represented by the reception can be
         * received successfully or not. This function must be purely functional
         * and support optimistic parallel computation.
         */
        virtual bool computeIsReceptionPossible(const IListening *listening, const IReception *reception) const = 0;

        /**
         * Returns whether the reception is actually attempted or ignored by the
         * receiver. This function must be purely functional and support optimistic
         * parallel computation.
         */
        virtual bool computeIsReceptionAttempted(const IListening *listening, const IReception *reception, const std::vector<const IReception *> *interferingReceptions) const = 0;

        /**
         * Returns the result of the reception process specifying whether it was
         * successful or not and any other physical properties. This function must
         * be purely functional and support optimistic parallel computation.
         */
        virtual const IReceptionDecision *computeReceptionDecision(const IListening *listening, const IReception *reception, const std::vector<const IReception *> *interferingReceptions, const INoise *backgroundNoise) const = 0;
};

}

} //namespace


#endif