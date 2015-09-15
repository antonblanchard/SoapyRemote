// Copyright (c) 2015-2015 Josh Blum
// SPDX-License-Identifier: BSL-1.0

#pragma once
#include "SoapyRemoteConfig.hpp"
#include <cstddef>

class SoapyRPCSocket;

/*!
 * The recv endpoint supports datagram reception over a windowed link.
 */
class SOAPY_REMOTE_API SoapyRecvEndpoint
{
public:
    SoapyRecvEndpoint(
        SoapyRPCSocket &sock,
        const size_t numChans,
        const size_t buffSize,
        const size_t numBuffs);

    ~SoapyRecvEndpoint(void);

    //! Actual buffer size in bytes
    size_t getBuffSize(void) const;

    //! Actual number of buffers
    size_t getNumBuffs(void) const;

    //! Query handle addresses
    void getAddrs(const size_t handle, void **buffs) const;

    /*!
     * Wait for a datagram to arrive at the socket
     * return true when ready for false for timeout.
     */
    bool wait(const long timeoutUs);

    /*!
     * Acquire a receive buffer with metadata.
     */
    int acquire(size_t &handle, const void **buffs, int &flags, long long &timeNs);

    /*!
     * Release the buffer when done.
     */
    void release(const size_t handle);

private:
    SoapyRPCSocket &_sock;
};
