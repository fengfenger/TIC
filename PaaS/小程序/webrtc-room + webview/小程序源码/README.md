# TAvKit

TAVKit是一个音视频组件库，提供音视频通话、通用界面布局能力。

> 如果还没有开通腾讯云实时音视频服务，请参考[开通实时音视频服务](https://cloud.tencent.com/document/product/647/17195)文档进行开通。

## TAvKit集成

### 1. 组件源码
[下载](http://)

### 2. 组件目录结构介绍

| 目录 | 描述 |
| --- | ---- |
| tavkit-component | 视频通话组件 |
| dialog-component | 对话框组件 |
| elk-component | 日志上报组件 |
| event-component | 事件组件 |
| libs | 依赖库文件 |
| request-component | 网络组件 |
| webim-component | im组件 |
| webrtc-room | 音视频组件 |

> tavkit-component组件依赖dialog-component，elk-component，event-component，libs，request-component，webim-component，webrtc-room组件，对外只需要使用tavkit-component组件即可。

### 3. 快速集成

#### 3.1 申请小程序账号
请在[微信公众平台](https://mp.weixin.qq.com/)申请小程序号，需要注意：出于政策和合规的考虑，微信暂时没有放开所有小程序对实时音视频功能（即&lt;live-pusher&gt;和&lt;live-player&gt;标签）的支持：

> 个人账号和企业账号的小程序暂时只开放如下表格中的类目

|主类目|子类目|
|-----| ------|
|【社交】 | 直播 |
|【教育】 | 在线教育 |
|【医疗】 | 互联网医院，公立医院 |
|【政务民生】 | 所有二级类目 |
|【金融】 | 基金、信托、保险、银行、证券/期货、非金融机构自营小额贷款、征信业务、消费金融 |

#### 3.2 开通实时音视频组件权限
在【微信公众平台】-【开发】-【接口设置】中自助开通该组件权限，如下图所示：
![](https://camo.githubusercontent.com/cf218c84eb39da8498e152e425a9ed2538c5b659/68747470733a2f2f6d632e71636c6f7564696d672e636f6d2f7374617469632f696d672f61333464663565336538366339623066636466626138366638353736653036612f77656978696e7365742e706e67)

#### 3.3 配置服务器安全域名
组件内部需要访问如下地址，请将以下域名在 【微信公众平台】-【开发】-【开发设置】-【服务器域名】中进行配置，添加到 request 合法域名中：

| 域名 | 说明 |
|----|----|
| https://official.opensso.tencent-cloud.com | WebRTC音视频鉴权服务域名|
| https://yun.tim.qq.com | WebRTC音视频鉴权服务域名|
| https://cloud.tencent.com | 推流域名|
| https://webim.tim.qq.com | IM域名|
| https://ilivelog.qcloud.com | 日志上报域名 |


#### 3.4 新建小程序项目
下载并安装最新版本的[微信开发者工具](https://developers.weixin.qq.com/miniprogram/dev/devtools/download.html)，使用小程序绑定的微信号扫码登录开发者工具。

![](https://main.qcloudimg.com/raw/8e1eeee23aec979f346d4b4c05e62571.png)

#### 3.5 按目录结构将下载的代码覆盖到新建的小程序中

> 在将代码覆盖完成欧，参考[快速接入文档](https://cloud.tencent.com/document/product/647/32399)，生成相应的测试账号，覆盖\tavkit\wx\miniprogram\pages\tavkit\account.js的内容，即可快速跑通Demo


#### 3.6 tavkit组件的使用
在page页面中使用组件
比如新建一个index的页面，会生成index.js，index.json，index.wxml，index.wxss文件

在index.json中申明要使用的插件

```
{
  "usingComponents": {
    "tavkit-component": "../../../component_chat/tavkit-component/tavkit-component"
  }
}
```

申明好插件后，即可在index.wxml文件中使用tavkit组件

index.wxml布局
```
<tavkit-component class="av-box" id="tAvKitComponent"></tavkit-component>
```

index.wxss设置样式
```
.av-box {
  width: 100vw;
  height: 100vh;
}
```

#### 3.7 启动插件
在完成3.6的步骤后，即可启动插件。

在页面index.js的生命周期onLoad回调中，先获取组件，最后调用组件的start方法，即可完成开始启动插件进行音视频通话。

index.js
```
onLoad() {
  var tavKitComponent = this.selectComponent('#tAvKitComponent');
  tavKitComponent.start({
    userId: this.data.userId,
    userSig: this.data.userSig,
    sdkAppId: this.data.sdkAppId,
    roomId: this.data.roomId,
    listener: {
      onUserInfoListener(userids, callback) {
        callback([{
          userId: "mini_vc_01",
          userName: "小程序1",
          avatarUrl: "https://is1-ssl.mzstatic.com/image/thumb/Purple118/v4/c1/af/fe/c1affef6-5542-29fb-0f46-14687e0966bd/AppIcon-0-1x_U007emarketing-0-0-85-220-0-7.png/320x0w.jpg"
        }]);
      },

      onSwitchCameraListener(front) {
        console.error(' front:', front);
      },

      onMutedListener(muted) {
        console.error(' muted:', muted);
      },

      onHandupListener: this.handupEventListener,
      onErrorListener: this.errorEventListener
    }
  });
}
```

#### 3.8 组件方法详解

##### 3.8.1 start
| 方法 | 参数| 描述 |
| -- | -- | -- |
| start | options |组件的入口函数，通过调用此方法，即可启动组件 |

options参数详解

| 参数名 | 类型 | 是否必填 | 描述 |
| -- | -- | -- | -- |
| sdkAppId | Number | 是 | 开通实时音视频服务创建应用后分配的 sdkAppId |
| userId | String | 是 | 通话人的userid |
| userSig | String | 是 | 身份签名，相当于登录密码的作用 |
| roomId | Number | 是 | 房间号 |
| privateMapKey | String | 否 | 进房秘钥（如果在实时音视频控制台的应用启用权限密钥，则为必填） |
| listener.onUserInfoListener | Function | 否 | 用户信息回调 |
| listener.onSwitchCameraListener | Function | 否 | 切换前后摄像头操作回调 |
| listener.onMutedListener | Function | 否 | 静音按钮的操作回调 |
| listener.onHandupListener | Function | 否 | 挂断按钮的操作回调 |
| listener.onErrorListener | Function | 否 | 错误信息回调 |

##### 3.8.2 listener.onUserInfoListener

> 对端用户进房后，组件内部会回调onUserInfoListener，会将userid和callback回调出来

| 参数名 | 类型 | 描述 |
| -- | -- | -- |
| userIds | Array | 对端的用户的userid |
| callback | Function | 将用户的信息回调给组件内部，目前支持设置用户名称和头像(支持批量设置) |

格式如下：
```
onUserInfoListener(userids, callback) {
  callback([{
    userId: "mini_vc_01",
    userName: "小程序1",
    avatarUrl: "https://is1-ssl.mzstatic.com/image/thumb/Purple118/v4/c1/af/fe/c1affef6-5542-29fb-0f46-14687e0966bd/AppIcon-0-1x_U007emarketing-0-0-85-220-0-7.png/320x0w.jpg"
  }]);
},
```

##### 3.8.3 listener.onSwitchCameraListener

> 切换摄像头回调

| 参数名 | 类型 | 描述 |
| -- | -- | -- |
| front | Boolean | true：前置摄像头  false：后置摄像头 |

##### 3.8.4 listener.onMutedListener

> 静音回调（静音：是否静自己的音，相当于禁用麦克风）

| 参数名 | 类型 | 描述 |
| -- | -- | -- |
| muted | Boolean | true：静音  false：不静音 |


##### 3.8.5 listener.onHandupListener

> 挂断回调

##### 3.8.6 listener.onErrorListener

> 错误回调

| 参数名 | 类型 | 描述 |
| -- | -- | -- |
| error | Object | 错误回调内容 |

> error详解

| 参数名 | 类型 | 描述 |
| -- | -- | -- |
| module | String | 错误模块，分为trtc,server,http,avkit |
| errorCode | String | 错误码 |
| errorMsg | String | 错误信息 |

> trtc错误码

| 错误码 |描述 |
| -- | -- |
| -1301 | 打开摄像头失败|
| -1302 | 打开麦克风失败|
| -1307 | 推流连接断开|
| -1019 | 进房失败或者退房成功|
| 10001 | 请先对摄像头进行授权|
| 10002 | 请先对麦克风进行授权|
| 5000 | 退出通话|

> server服务器错误

| 错误码 |描述 |
| -- | -- |
| 10000 |  服务器错误 |
| 10001 |  解析url或者请求body错误 |
| 10002 |  json序列列化失败 |
| 10003 |  json反序列列化失败 |
| 10004 |  参数无效 |
| 10005 |  未授权 |
| 10006 |  数据库请求错误 |
| 14000 |  进房失败 |
| 14001 |  退房失败 |
| 14002 |  参数中的房间号与用户当前的房间号不不匹配 |
| 14003 |  房间已经关闭 |
| 14004 |  用户已经退出房间 |
| 14005 |  更新心跳错误 |
| 14006 |  查询房间内用户信息错误 |
| 14007 |  没找到对应UUID的房间 |
| 14008 |  获取录制文件失败 |

> http错误

| 错误码 |描述 |
| -- | -- |
| 10000 | 服务器或者网络错误 |

> avkit错误

| 错误码 |描述 |
| -- | -- |
| 10001 | 没有权限使用视频组件 |
| 10002 | 缺少必要参数userId |
| 10003 | 缺少必要参数sdkAppId |
| 10004 | 缺少必要参数userSig |
| 10005 | 缺少必要参数roomId |
| 70346 | 缺少必要参数userSig |
| 80 | 进房秘钥privateMapKey不能为空 |
| 82 | 参数检测失败 |
| 86 | 进房秘钥privateMapKey已过期 |
| 87 | 进房秘钥privateMapKey不正确 |
| 88 | 还没有购买实时音视频套餐包 |