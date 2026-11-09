/*
 * ============================================================================
 * 【中文导读】message_queue.cpp —— 基带线程与 UI 线程的消息通道
 * ----------------------------------------------------------------------------
 * 实时信号处理的命脉：基带线程（绝不能阻塞）产生的频谱/音频数据以
 * 消息对象投递到 UI 线程消费。MessageHandlerRegistry 按 ID 分发——
 * 大型 RTOS 工程做"生产者-消费者"解耦的标准姿势。
 * ============================================================================
 */

/*
 * Copyright (C) 2015 Jared Boone, ShareBrained Technology, Inc.
 *
 * This file is part of PortaPack.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include "message_queue.hpp"

#include "lpc43xx_cpp.hpp"
using namespace lpc43xx;

#if defined(LPC43XX_M0)
void MessageQueue::signal() {
    creg::m0apptxevent::assert_event();
}
#endif

#if defined(LPC43XX_M4)
void MessageQueue::signal() {
    creg::m4txevent::assert_event();
}
#endif
