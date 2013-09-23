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

#include <bakge/Bakge.h>

namespace bakge
{

Result GetPrimaryMonitorResolution(int* StoreX, int* StoreY)
{
    GLFWmonitor* PrimaryMonitor = glfwGetPrimaryMonitor();
    if(PrimaryMonitor == NULL) {
        printf("Error getting primary monitor\n");
        return BGE_FAILURE;
    }

    const GLFWvidmode* MonitorVideoMode = glfwGetVideoMode(PrimaryMonitor);
    if(MonitorVideoMode == NULL) {
        printf("Error getting primary monitor video mode\n");
        return BGE_FAILURE;
    }

    *StoreX = MonitorVideoMode->width;
    *StoreY = MonitorVideoMode->height;

    return BGE_SUCCESS;
}


Result GetPrimaryMonitorPhysicalSize(int* StoreX, int* StoreY)
{
    GLFWmonitor* PrimaryMonitor = glfwGetPrimaryMonitor();
    if(PrimaryMonitor == NULL) {
        printf("Error getting primary monitor\n");
        return BGE_FAILURE;
    }

    glfwGetMonitorPhysicalSize(PrimaryMonitor, StoreX, StoreY);

    return BGE_SUCCESS;
}


int GetNumberMonitors()
{
    int MonitorCount;
    if(glfwGetMonitors(&MonitorCount) == NULL)
        return -1;

    return MonitorCount;
}

} /* bakge */
