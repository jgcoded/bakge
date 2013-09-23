/* *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013 Paul Holden et al. (See AUTHORS)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * */

/*!
 * @file Device.h
 * @brief Video/audio device API.
 */

#ifndef BAKGE_SYSTEM_DEVICE_H
#define BAKGE_SYSTEM_DEVICE_H

#include <bakge/Bakge.h>

namespace bakge
{

/*! @brief Get the resolution of the primary monitor.
 *
 * Get the resolution of the primary monitor.
 *
 * @param[out] StoreX Pointee set to screen resolution width.
 * @param[out] StoreY Pointee set to screen resolution height.
 *
 * @return BGE_FAILURE if any errors occurred. In such a case, *StoreX and
 * *StoreY are not modified. BGE_SUCCESS otherwise.
 */
BGE_FUNC Result GetPrimaryMonitorResolution(int* StoreX, int* StoreY);

/*! @brief Get the physical size in millimeters of the primary monitor.
 *
 * Get the physical size in millimeters of the primary monitor.
 *
 * @param[out] StoreX Pointee set to monitor's physical width.
 * @param[out] StoreY Pointee set to monitor's physical height.
 *
 * @return BGE_FAILURE if any errors occurred. In such a case, *StoreX and
 * *StoreY are not modified. BGE_SUCCESS otherwise.
 */
BGE_FUNC Result GetPrimaryMonitorPhysicalSize(int* StoreX, int* StoreY);

/*! @brief Get the number of attached monitors.
 *
 * Get the number of attached monitors.
 *
 * @return Number of attached monitors; -1 if any errors occurred.
 */
BGE_FUNC int GetNumberMonitors();

} /* bakge */

#endif /* BAKGE_SYSTEM_DEVICE_H */
