# IMsoftware
即时聊天软件服务器集群

I/O模型：Reactor事件驱动模式



## 依赖

- C++17
- hiredis库
- mysql库
- Libevent库
- Json for modern C++



## 使用

```
mkdir build
cd build
cmake ..
make
```





## 实现思路





### 数据库表：

#### User表：

| 字段名称  | 类型        | 说明         | 约束                        |
| --------- | ----------- | ------------ | --------------------------- |
| _id       | int         | 用户唯一标识 | PRIMARY KEY，AUTO_INCREMENT |
| _name     | VARCHAR(32) | 用户名       | NOT NULL                    |
| _password | VARCHAR(32) | 用户密码     | NOT NULL                    |
| _state    | int         | 用户状态     |                             |

#### Friend表：

| 字段名称  | 类型 | 说明         | 约束                        |
| --------- | ---- | ------------ | --------------------------- |
| _id       | int  | 唯一标识     | PRIMARY KEY，AUTO_INCREMENT |
| _userID   | int  | 用户id       | FOREIGN KEY                 |
| _friendID | int  | 好友id       | FOREIGN KEY                 |
| _state    | int  | 好友关系状态 | NOT NULL                    |

#### OfflineMsg表：

| 字段名称 | 类型 | 说明     | 约束        |
| -------- | ---- | -------- | ----------- |
| _id      | int  | 消息标识 | NOT NULL    |
| _fromID  | int  | 发送者id | FOREIGN KEY |
| _toID    | int  | 接受者id | FOREIGN KEY |



### 通信协议的设计：

TCP协议是数据流协议，底层根据二进制缓冲区的实际情况进行包的划分，会出现半包、粘包问题。通过设计通信协议来处理半包、粘包问题。

包头：

| 字段名  | 字段类型 | Request            |
| :------ | :------- | :----------------- |
| magic   | int      | 是否有效           |
| code    | 整数     | 应答结果代码       |
| version | 整数     | 请求发起方程序版本 |
| len     | int      | 负载大小           |
