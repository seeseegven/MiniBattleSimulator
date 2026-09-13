# Mini Battle Simulator

基于 C++20 开发的 Windows 控制台回合制战斗模拟器，支持本地 PVE 与双人联网 PVP。项目将战斗规则抽离为 Core 静态库，由客户端复用本地逻辑、服务端负责联网战局判定，以实践面向对象设计、资源管理、多线程同步和 TCP 网络编程。

## 核心功能

- 本地 PVE：玩家与 AI 敌人进行回合制战斗，支持中途退出
- 联网 PVP：两名客户端自动匹配，由服务端初始化并维护权威战局，支持跨设备连接
- 五种技能：伤害、单次治疗、持续治疗与防御提升，包含冷却机制
- 状态效果：按回合执行持续效果，并自动清理过期状态
- 敌人 AI：根据技能收益评分自动选择行动
- 战斗表现：同步展示角色属性、当前回合、技能冷却与行动结果
- 完整生命周期：胜负通知、中途退出、线程与 Socket 回收，可连续进行多局 PVE/PVP

## 技术栈

`C++20` · `Visual Studio 2022` · `STL` · `Winsock2` · `std::thread` · `mutex` · `atomic`

## 项目架构

```mermaid
flowchart LR
    C1["BattleSimulator<br/>客户端 1"] -->|"技能指令"| Server["MiniBattleServer<br/>权威战斗服务端"]
    C2["BattleSimulator<br/>客户端 2"] -->|"技能指令"| Server
    Server -->|"战局状态广播"| C1
    Server -->|"战局状态广播"| C2
    C1 --> Core["MiniBattleCore<br/>战斗核心静态库"]
    C2 --> Core
    Server --> Core
    Core --> Rules["角色 / 技能 / 状态 / AI / 战斗管理"]
```

| 模块 | 主要职责 |
| --- | --- |
| `MiniBattleCore` | 管理角色、技能、状态效果、AI、回合规则与战局数据 |
| `BattleSimulator` | 菜单状态机、本地 PVE、网络收发、状态解析与控制台渲染 |
| `MiniBattleServer` | 双人匹配、PVP 初始化、指令校验、权威结算、广播与连接回收 |
| `MiniBattleClient` | 独立的 Winsock 通信测试客户端 |

## 工作流程

### 本地 PVE

输入 `b` 后，客户端通过 Core 创建玩家和敌人；`BattleManager` 推进回合，玩家选择技能，敌人 AI 根据收益评分行动，直至战斗结束或玩家输入 `z` 返回菜单。

```text
Game → BattleManager → CharacterManager → Player / Enemy → Skill / EffectStatus
```

### 联网 PVP

1. 两个客户端输入 `n` 并连接服务端 `8888` 端口。
2. 服务端将连接加入匹配队列，人数满足后创建 PVP `BattleManager`。
3. 客户端只发送技能编号；服务端校验玩家身份、行动顺序和技能冷却。
4. 服务端完成技能结算，将角色属性、回合、冷却和行动信息广播给双方。
5. 客户端持续接收数据直至 `\r` 消息结束符，再解析完整数据并刷新界面。
6. 角色死亡时双方分别收到胜负通知；一方退出时服务端中断战局，回收连接后可重新匹配。

## 设计亮点

- 通过 `Character`、`Skill` 等抽象接口实现运行时多态，降低角色与技能扩展成本。
- 使用 `unique_ptr`、移动语义和 RAII 管理角色、技能及战局生命周期。
- 使用 `std::function` 与技能工厂集中维护伤害、治疗和增益计算规则。
- Core 静态库同时供客户端和服务端复用，避免两端重复实现战斗规则。
- PVP 采用服务端权威模型，客户端只提交操作，服务端负责校验与状态推进。
- 服务端使用独立通信线程、消息队列、互斥锁和原子状态协调双客户端战斗。
- 自定义文本通信格式并使用 `\r` 标记消息边界，循环接收以避免 TCP 分包导致不完整解析。
- 客户端对比前后状态，以颜色高亮生命值、伤害、治疗和防御变化。
- 对网络线程和 Socket 生命周期进行收尾，使客户端可在 PVE、PVP 和菜单间循环切换。

## 构建与运行

环境要求：Windows 10/11、Visual Studio 2022、MSVC v143。

```powershell
msbuild .\MiniBattleSimulator.sln /p:Configuration=Debug /p:Platform=x64
```

- 本地模式：启动 `BattleSimulator`，输入 `b`。
- 联网模式：先启动 `MiniBattleServer`，再启动两个 `BattleSimulator`，分别输入 `n`。
- 默认服务端地址配置在 `BattleSimulator/game.cpp`；跨设备运行时需设置为服务端的局域网或虚拟局域网 IP，并开放 TCP `8888` 端口。
- 技能选择：输入 `1`～`5`；主菜单输入 `q` 退出。

## 简历描述参考

> 使用 C++20 开发支持 PVE/PVP 的控制台回合制战斗模拟器，将角色、技能、状态效果及战斗规则抽离为 Core 静态库；基于继承、多态、智能指针和函数对象实现可扩展技能体系与收益评分 AI；使用 Winsock2、多线程、消息队列、互斥锁和原子变量实现跨设备双客户端匹配，通过自定义消息边界解决 TCP 分包解析问题，并采用服务端权威模型完成回合校验、技能结算、状态同步及连接回收。
