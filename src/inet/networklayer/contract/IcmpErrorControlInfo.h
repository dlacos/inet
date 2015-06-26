#ifndef __INET_ICMPERRORCONTROLINFO_H
#define __INET_ICMPERRORCONTROLINFO_H


#include "inet/networklayer/contract/IcmpErrorControlInfo_m.h"

namespace inet {

class INET_API IcmpErrorControlInfo : public IcmpErrorControlInfo_Base
{
  public:
    IcmpErrorControlInfo() : IcmpErrorControlInfo_Base() {}
    IcmpErrorControlInfo(const IcmpErrorControlInfo& other) : IcmpErrorControlInfo_Base(other) {}
    IcmpErrorControlInfo& operator=(const IcmpErrorControlInfo& other) {if (this==&other) return *this; IcmpErrorControlInfo_Base::operator=(other); return *this;}
    virtual IcmpErrorControlInfo *dup() const {return new IcmpErrorControlInfo(*this);}

    virtual L3Address getSourceAddress() const { return _getSourceAddress(); }
    virtual L3Address getDestinationAddress() const { return _getDestinationAddress(); }
};

} // namespace inet

#endif // ifndef __INET_ICMPERRORCONTROLINFO_H

