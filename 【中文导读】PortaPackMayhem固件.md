# PortaPack Mayhem（便携 SDR 固件）学习导读

> 目录：`04-项目实战/mayhem-firmware-便携SDR固件`
> 来源：https://github.com/portapack-mayhem/mayhem-firmware （约 5.5k star）

## 这是什么

PortaPack 是 **HackRF One**（开源软件定义无线电）的触摸屏扩展板，Mayhem 固件给它装上了独立工作能力：频谱扫描、收音/广播 RDS、各种无线信号收发、GPS、音频分析……**复杂度是本清单里最高的一档**：C++ 大型工程、实时信号处理（基带 DSP）、ChibiOS RTOS、触摸 UI、FPGA/CPLD 协同。适合作为"进阶综合研究项目"，读懂其中一两个子系统就有巨大收获。

⚠️ 合规提醒：射频发射功能在各国受法规管制，学习请遵守当地无线电管理条例，只做接收/实验室实验。

## 目录导读

| 目录/文件 | 内容 |
| --- | --- |
| `firmware/`（common/application/…） | 主固件：`application/` 各 App、`common/` 公共库 |
| `application/apps/` | 每个功能一个 App：频谱、接收机、发射工具、GPS... |
| `application/external/` | 外部插件 App 生态 |
| `common/` | DSP、UI 框架、通信协议、文件系统封装 |
| `hackrf/` | HackRF 平台代码（ARM + CPLD 配置） |
| `sdcard/` | SD 卡内容（世界机场数据库等资源说明） |
| `docker/` | 一键 Docker 构建环境（推荐用这个编译） |

## 学习路径（建议）

1. 先读官方 wiki（GitHub Wiki）的 PortaPack 版本对照（H2/H2M/H4M），确认硬件代次。
2. 用 `docker compose` 构建（`dockerfile` 已备好全工具链），产物 `*.ppfw.bin` 刷机。
3. 挑两个 App 对比读：`apps/ui_spectrum_app.cpp`（实时 FFT 频谱）与 `apps/ui_receiver_app.cpp`（音频接收链路），跟着数据流走：IQ 采样 → baseband 线程 → DSP → UI 显示。
4. 研究消息机制：`message_queue` 在基带线程与 UI 线程间搬运数据——大型 RTOS 工程的线程分工范本。
5. 进阶：读 `common/dsp/` 的 FIR/FFT 实现与 FPGA 侧基带配置。

## 学习要点

1. **实时信号处理架构**：采样率即死线，基带线程绝不允许阻塞——看它如何做无锁/低延迟消息传递。
2. **UI 框架**：自研 Widget 树（不是 LVGL），大屏触摸 UI 在 RTOS 上的组织方式。
3. **C++ 嵌入式范式**：模板、RAII、placement new 在 MCU 上的使用边界。
4. **SD 卡文件系统**：FATFS 上存 WAV/CAP 截获数据、机场库、地图。

## 建议购买/准备

- **HackRF One**（克隆版 ¥400-800，正品 Great Scott Gadgets $350+）——**本项目必须**
- **PortaPack H2/H4M 扩展板**（¥300-600，H4M 带电池与喇叭；注意买"Mayhem 兼容"版本）
- 天线套装（ telescopic 天杆 + 20MHz-6GHz 各频段，¥50-100）
- 数据线、（可选）TCXO 升级件
- **总预算：¥700-1500**（预算有限可先只买 HackRF 玩接收，PortaPack 后补）
- 纯读代码：0 元，装 Docker 即可构建。

## 学习目标（自测）

- [ ] Docker 构建出固件并刷机
- [ ] 画出从天线到屏幕的一条完整接收链路
- [ ] 说清基带线程与 UI 线程的消息传递机制
- [ ] 用频谱 App 解释 FFT 分辨率带宽（RBW）概念
