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

#ifndef __INET_NARROWBANDTRANSMISSIONBASE_H
#define __INET_NARROWBANDTRANSMISSIONBASE_H

#include "inet/physicallayer/base/TransmissionBase.h"
#include "inet/physicallayer/contract/IModulation.h"
#include "inet/physicallayer/contract/IRadioSignal.h"

namespace inet {

namespace physicallayer {

class INET_API NarrowbandTransmissionBase : public TransmissionBase, public virtual INarrowbandSignal
{
  protected:
    const IModulation *modulation;
    const int headerBitLength;
    const int payloadBitLength;
    const Hz carrierFrequency;
    const Hz bandwidth;
    const bps bitrate;

  public:
    NarrowbandTransmissionBase(const IRadio *transmitter, const cPacket *macFrame, const simtime_t startTime, const simtime_t endTime, const Coord startPosition, const Coord endPosition, const EulerAngles startOrientation, const EulerAngles endOrientation, const IModulation *modulation, int headerBitLength, int payloadBitLength, Hz carrierFrequency, Hz bandwidth, bps bitrate);

    virtual void printToStream(std::ostream& stream) const override;
    virtual const IModulation *getModulation() const { return modulation; }
    virtual int getHeaderBitLength() const { return headerBitLength; }
    virtual int getPayloadBitLength() const { return payloadBitLength; }
    virtual Hz getCarrierFrequency() const { return carrierFrequency; }
    virtual Hz getBandwidth() const { return bandwidth; }
    virtual bps getBitrate() const { return bitrate; }
};

} // namespace physicallayer

} // namespace inet

#endif // ifndef __INET_NARROWBANDTRANSMISSIONBASE_H
