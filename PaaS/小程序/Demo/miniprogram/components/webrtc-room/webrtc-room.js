const CONSTANT = require('../../constant/Constant');

Component({
  /**
   * 组件的属性列表
   */
  properties: {
    roomID: {
      type: Number,
      value: 0
    },
    userID: {
      type: String,
      value: ''
    },

    userSig: {
      type: String,
      value: ''
    },

    sdkAppID: {
      type: Number,
      value: 0
    },

    accountType: {
      type: Number,
      value: 0
    },
    privateMapKey: {
      type: String,
      value: ''
    },
    template: {
      type: String,
      value: '',
      observer: function (newVal) {
        this.initLayout(newVal)
      }
    }, //使用的界面模版
    whiteness: {
      type: String,
      value: 5
    },
    beauty: {
      type: String,
      value: 5
    }, //美颜程度，取值为0~9
    aspect: {
      type: String,
      value: '3:4'
    }, //设置画面比例，取值为'3:4'或者'9:16'
    minBitrate: {
      type: Number,
      value: 400
    }, //设置码率范围为[minBitrate,maxBitrate]，四人建议设置为200~400
    maxBitrate: {
      type: Number,
      value: 800
    },
    muted: {
      type: Boolean,
      value: false
    }, //设置推流是否静音
    debug: {
      type: Boolean,
      value: false
    }, //是否显示log

    enableCamera: {
      type: Boolean,
      value: true
    },

    waitingImg: {
      type: String,
      value: ''
    },

    // live-player的背景图
    playerBackgroundImg: {
      type: String,
      value: ''
    },

    pusherBackgroundImg: {
      type: String,
      value: ''
    },

    loadingImg: {
      type: String,
      value: ''
    },

    // 纯音频推流
    pureAudioPushMod: {
      type: Number,
      value: 0
    },

    // 录制文件的ID
    recordId: {
      type: Number,
      value: null
    },
  },

  /**
   * 组件的初始数据
   */
  data: {
    self: {},
    msgBoxScrollTop: 0,
    requestSigFailCount: 0,
    hasExitRoom: true,
    pusherContext: '',
    pushURL: '',
    members: [{}, {}, {}],
    maxMembers: 3,
    roomTag: 'ok',
    CONSTANT,
    startPlay: false,
    originPushURL: '',
    showMsgBox: false, // 显示msg
    msgs: [],
    inputFocus: false, //默认不获得焦点
    chatMsg: ''
  },

  ready() {},

  detached() {
    this.exitRoom();
  },

  /**
   * 组件的方法列表
   */
  methods: {
    /**
     * 初始化布局，当template改变时
     * @param {*} templateName 
     */
    initLayout(templateName) {
      self = this;
      switch (templateName) {
        case '1v1':
          this.setData({
            maxMembers: 1,
            members: [{}],
            template: templateName
          });
          break;
        default:
          break
      }
    },

    /**
     * webrtc-room程序的入口
     */
    start: function (isNetWorkChange) {
      this.data.hasExitRoom = false;

      // 如果有推流地址了,且只是网络变化，则不再获取推流
      if (this.data.originPushURL && isNetWorkChange) {
        this.setData({
          pushURL: this.data.originPushURL + '&tx_time=' + new Date().getTime()
        })
      } else {
        // 获取推流url
        this.requestSigServer(this.data.userSig, this.data.privateMapKey);
      }
    },

    /**
     * 停止
     */
    stop: function () {
      this.data.hasExitRoom = true;
      this.exitRoom();
    },

    /**
     * 暂停
     */
    pause: function () {
      if (!this.data.pusherContext) {
        this.data.pusherContext = wx.createLivePusherContext('rtcpusher', this);
      }
      this.data.pusherContext && this.data.pusherContext.pause();

      this.data.members.forEach(function (val) {
        val.playerContext && val.playerContext.pause();
      });
    },

    resume: function () {
      if (!this.data.pusherContext) {
        this.data.pusherContext = wx.createLivePusherContext('rtcpusher', this);
      }
      this.data.pusherContext && this.data.pusherContext.resume();

      this.data.members.forEach(function (val) {
        val.playerContext && val.playerContext.resume();
      });
    },

    /**
     * 切换摄像头
     */
    switchCamera: function () {
      if (!this.data.pusherContext) {
        this.data.pusherContext = wx.createLivePusherContext('rtcpusher', this);
      }
      this.data.pusherContext && this.data.pusherContext.switchCamera({});
    },

    /**
     * 退出房间
     */
    exitRoom: function () {
      if (!this.data.pusherContext) {
        this.data.pusherContext = wx.createLivePusherContext('rtcpusher', this);
      }
      this.data.pusherContext && this.data.pusherContext.stop && this.data.pusherContext.stop();

      this.data.members.forEach(function (val) {
        val.playerContext && val.playerContext.stop();
      });

      for (var i = 0; i < this.data.maxMembers; i++) {
        this.data.members[i] = {};
      }

      this.setData({
        members: self.data.members
      });
    },



    /**
     * 请求SIG服务
     */
    requestSigServer: function (userSig, privMapEncrypt) {
      var self = this;
      var roomID = this.data.roomID * 1;
      var userID = this.data.userID;
      var sdkAppID = this.data.sdkAppID;

      var host = "https://official.opensso.tencent-cloud.com";
      var url = host + "/v4/openim/jsonvideoapp?sdkappid=" + sdkAppID + "&identifier=" + userID + "&usersig=" + userSig + "&random=9999&contenttype=json";

      var reqHead = {
        "Cmd": 1,
        "SeqNo": Math.round(Math.random() * 100000),
        "BusType": 7,
        "GroupId": roomID
      };

      var reqBody = {
        "PrivMapEncrypt": privMapEncrypt,
        "TerminalType": 1,
        "FromType": 3,
        "SdkVersion": 26280566
      };

      console.log("requestSigServer params:", url, reqHead, reqBody);

      wx.request({
        url: url,
        data: {
          "ReqHead": reqHead,
          "ReqBody": reqBody
        },
        method: "POST",
        success: function (res) {
          console.log("requestSigServer success:", res);

          /**
           * 80	进房秘钥privateMapKey不能为空
            82	参数检测失败
            86	进房秘钥privateMapKey已过期
            87	进房秘钥privateMapKey不正确
            88	还没有购买实时音视频套餐包
            *
           */

          if (res.data["ErrorCode"] || res.data["RspHead"]["ErrorCode"] != 0) {
            self.postErrorEvent(CONSTANT.ROOM.ERROR_REQUEST_ROOM_SIG, `error|code:${res.data["ErrorCode"] || res.data["RspHead"]["ErrorCode"]} |message:获取推流地址错误`);
            return;
          }
          var roomSig = JSON.stringify(res.data["RspBody"]);
          var pushUrl = `room://cloud.tencent.com?sdkappid=${sdkAppID}&roomid=${roomID}&userid=${userID}&roomsig=${encodeURIComponent(roomSig)}`;
          console.log("roomSigInfo", roomID, userID, roomSig, pushUrl);

          // 如果有配置纯音频推流或者recordId参数
          if (self.data.pureAudioPushMod || self.data.recordId) {
            var bizbuf = {
              Str_uc_params: {
                pure_audio_push_mod: 0,
                record_id: 0
              }
            }
            // 纯音频推流
            if (self.data.pureAudioPushMod) {
              bizbuf.Str_uc_params.pure_audio_push_mod = self.data.pureAudioPushMod
            } else {
              delete bizbuf.Str_uc_params.pure_audio_push_mod;
            }

            // 自动录制时业务自定义id
            if (self.data.recordId) {
              bizbuf.Str_uc_params.record_id = self.data.recordId
            } else {
              delete bizbuf.Str_uc_params.record_id;
            }
            pushUrl += '&bizbuf=' + encodeURIComponent(JSON.stringify(bizbuf));
          }

          self.setData({
            originPushURL: pushUrl,
            pushURL: pushUrl + '&tx_time=' + new Date().getTime()
          }, () => {

          });
        },
        fail: function (error) {
          console.log("requestSigServer error:", error);
          self.postErrorEvent(CONSTANT.ROOM.ERROR_REQUEST_ROOM_SIG, '获取推流地址错误');
        }
      })
    },

    onWebRTCUserListPush: function (msg) {
      if (!msg) {
        return;
      }
      var jsonDic = JSON.parse(msg);
      if (!jsonDic) {
        return;
      }
      var newUserList = jsonDic.userlist || [];
      if (!newUserList) {
        return;
      }

      var currentMemberIds = [];
      self.data.members.forEach((member) => {
        member.userID && currentMemberIds.push(member.userID);
      });

      if (currentMemberIds.length === 0) { // 第一次进入
        if (newUserList.length >= self.data.maxMembers + 1) { // 当前返回的player成员列表,超过了房间的最大人数，则说明该用户超员了
          self.postErrorEvent(CONSTANT.ROOM.ERROR_EXCEEDS_THE_MAX_MEMBER,
            `当前课堂超过最大人数${self.data.maxMembers + 1}`);
          self.stop();
          return;
        }
      }

      var players = [];
      newUserList && newUserList.forEach(function (val) {
        var pusher = {
          userID: val.userid,
          accelerateURL: val.playurl
        };
        players.push(pusher);
      });

      self.onPusherJoin({
        players: players
      });

      self.onPusherQuit({
        players: players
      });
    },

    //将在res.pushers中，但不在self.data.members中的流，加入到self.data.members中
    onPusherJoin: function (res) {
      let self = this;
      res.players.forEach(function (player) {
        var emptyIndex = -1;
        var isMember = false; // 是否已经是在房间内的成员
        // 获取当前成员里面的userid
        var memberIds = self.data.members.map(function (item) {
          return item.userID || '';
        }) || [];

        if (memberIds.indexOf(player.userID) > -1) {
          isMember = true; // 已经是成员了
        } else {
          // 如果不是成员，则需要查找出空位
          emptyIndex = memberIds.indexOf('');
        }

        // 如果不是成员 && 还有空位
        if (!isMember && emptyIndex != -1) {
          player.loading = false;
          player.playerContext = wx.createLivePlayerContext(player.userID, self);
          self.data.members[emptyIndex] = player;
        }
      });

      self.setData({
        members: self.data.members
      });
    },

    //将在self.data.members中，但不在res.players中的流删除
    onPusherQuit: function (res) {
      for (var i = 0; i < self.data.members.length; i++) {
        var needDelete = true;
        for (var j = 0; j < res.players.length; j++) {
          if (self.data.members[i].userID == res.players[j].userID) {
            needDelete = false;
          }
        }
        if (needDelete) {
          self.data.members[i] = {};
        }
      }

      self.setData({
        members: self.data.members
      });
    },

    // 删除对端（对端连接断开）
    delPusher: function (pusher) {
      for (var i = 0; i < self.data.members.length; i++) {
        if (self.data.members[i].userID == pusher.userID) {
          var player = wx.createLivePlayerContext(pusher.userID, self);
          player && player.stop();
          self.data.members[i] = {};
          break;
        }
      }
      self.setData({
        members: self.data.members
      });
    },

    // 推流事件
    onPush: function (e) {
      if (!self.data.pusherContext) {
        self.data.pusherContext = wx.createLivePusherContext('rtcpusher', self);
      }
      var code;
      if (e.detail) {
        code = e.detail.code;
      } else {
        code = e;
      }

      if (code != 1020) {
        self.postEvent('elk-log', code, e.detail.message);
      }

      switch (code) {
        case 1002: {
          console.log('推流成功');
          self.postEvent(self.data.roomTag, CONSTANT.ROOM.SUCC_PUSH, '推流成功');
          break;
        }
        case -1301: {
          console.error('打开摄像头失败: ', code);
          self.postErrorEvent(CONSTANT.ROOM.ERROR_OPEN_CAMERA, '打开摄像头失败');
          self.exitRoom();
          break;
        }
        case -1302: {
          console.error('打开麦克风失败: ', code);
          self.postErrorEvent(CONSTANT.ROOM.ERROR_OPEN_MIC, '打开麦克风失败');
          self.exitRoom();
          break;
        }
        case -1307: {
          console.error('推流连接断开: ', code);
          self.postErrorEvent(CONSTANT.ROOM.ERROR_PUSH_DISCONNECT, '推流链接断开');
          self.exitRoom();
          break;
        }
        case 5000: {
          console.log('收到5000: ', code, new Date().getTime());
          // 收到5000就退房
          self.exitRoom();
          self.postErrorEvent(CONSTANT.ROOM.EXIT_ROOM, '退出房间');
          break;
        }
        case 1018: {
          console.log('进房成功', code);
          self.postEvent(self.data.roomTag, CONSTANT.ROOM.SUCC_JOIN_ROOM, '进房成功');
          break;
        }
        case 1019: {
          console.log('退出房间', code, new Date().getTime());
          self.postErrorEvent(CONSTANT.ROOM.ERROR_JOIN_ROOM, '进音视频房间错误');
          self.exitRoom();
          break;
        }
        case 1020: {
          console.log('成员列表', code, e.detail.message);
          self.onWebRTCUserListPush(e.detail.message);
          self.postEvent(self.data.roomTag, CONSTANT.ROOM.SUCC_MEMBERS_LIST, JSON.stringify(e.detail.message));
          break;
        }
        case 1021: {
          console.log('网络类型发生变化，需要重新进房', code);
          //先退出房间
          self.exitRoom();
          self.start(true);
          self.postEvent(self.data.roomTag, CONSTANT.ROOM.NETWORK_CHANGE, '网络类型发生变化，需要重新进房');
          break;
        }
        case 2007: {
          console.log('视频播放loading: ', e.detail.code);
          self.postEvent(self.data.roomTag, CONSTANT.ROOM.PUSHER_LOADING, '视频播放loading');
          break;
        }
        case 2004: {
          console.log('视频播放开始: ', e.detail.code);
          self.postEvent(self.data.roomTag, CONSTANT.ROOM.PUSHER_PLAY, '视频播放开始');
          break;
        }
        default: {
          // console.log('推流情况：', code);
        }
      }
    },

    // 标签错误处理
    onError: function (e) {
      console.log('推流错误：', e);
      var errorCode = (e.detail && e.detail.errCode) || (e.details && e.details.errCode);
      var errorMsg = '';
      switch (errorCode) {
        case 10001:
          errorMsg = '未获取到摄像头功能权限，请删除小程序后重新打开';
          self.postErrorEvent(CONSTANT.ROOM.ERROR_CAMERA_MIC_PERMISSION, errorMsg);
          break;
        case 10002:
          errorMsg = '未获取到录音功能权限，请删除小程序后重新打开';
          self.postErrorEvent(CONSTANT.ROOM.ERROR_CAMERA_MIC_PERMISSION, errorMsg);
          break;
      }
    },

    //播放器live-player回调
    onPlay: function (e) {
      self.data.members.forEach(function (val) {
        if (e.currentTarget.id == val.userID) {
          switch (e.detail.code) {
            case 2007: {
              console.log('视频播放loading: ', e);
              self.postEvent(self.data.roomTag, CONSTANT.ROOM.PLAYER_LOADING, val.userID);
              val.loading = true;
              break;
            }
            case 2004: {
              console.log('视频播放开始: ', e);
              self.postEvent(self.data.roomTag, CONSTANT.ROOM.PLAYER_PLAY, val.userID);
              val.loading = false;
              setTimeout(() => {
                self.setData({
                  startPlay: true
                });
              }, 500);
              break;
            }
            case -2301: {
              console.error('网络连接断开，且重新连接亦不能恢复，播放器已停止播放', val);
              // 记录失败信息
              self.postEvent(self.data.roomTag, CONSTANT.ROOM.PLAYER_DISCONNECT, val.userID);
              self.delPusher(val);
              break;
            }
            default: {
              // console.log('拉流情况：', e);
            }
          }
        }
      });

      self.setData({
        members: self.data.members
      });
    },

    /**
     * 是否启用摄像头
     * @param {*} enableCamera 
     */
    enableCamera(enable) {
      this.setData({
        enableCamera: enable
      });
    },

    /**
     * 是否启用麦克风
     * @param {*} enable (true 启用麦克风， false 关闭麦克风)
     */
    enableMicphone(enable) {
      this.setData({
        muted: !enable
      });
    },

    /**
     * 显示Input组件（input只有focus才是原生组件，才能显示出来）
     */
    showInput() {
      wx.nextTick(() => {
        this.setData({
          inputFocus: true
        });
      });
    },

    /**
     * 点击键盘的确认按钮
     * @param {*} event 
     */
    inputConfirm(event) {
      this.triggerEvent('InputEvent', {
        type: 'send',
        data: event.detail
      });
      this.setData({
        chatMsg: ''
      });
    },

    /**
     * input获得焦点
     */
    inputFocus() {},

    /**
     * input失去焦点
     */
    inputBlur() {
      this.setData({
        inputFocus: false
      });
    },

    postErrorEvent: function (errCode, errMsg) {
      this.postEvent('error', errCode, errMsg);
    },

    postEvent: function (tag, code, detail) {
      this.triggerEvent('RoomEvent', {
        tag: tag,
        code: code,
        detail: detail
      }, {});
    }
  }
})