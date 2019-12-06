/**
 * @file TEduBoard.h
 * @brief 腾讯云互动白板SDK for Window/Linux
 * @version 2.4.0.60
 */

#pragma once

#if defined(WIN32) //Windows

#ifdef EDUSDK_EXPORTS
#define EDUSDK_API __declspec(dllexport)
#else
#define EDUSDK_API __declspec(dllimport)
#endif

#include <windows.h>

#undef DeleteFile

#define WINDOW_HANDLE HWND

#else //Unix

#define EDUSDK_API __attribute__ ((visibility("default")))

#if defined(__APPLE__) //macOS

#ifdef __cplusplus
#ifdef __OBJC__
@class NSView;
#else
struct NSView;
#endif
#define WINDOW_HANDLE NSView*
#else
#define WINDOW_HANDLE void*
#endif

#else //Linux

#define WINDOW_HANDLE unsigned long

#endif

#endif

#include <cstdint>
#include <ostream>

class TEduBoardController;

/**
 * @defgroup ctrl TEduBoardController
 * 白板功能的主要接口类
 */

/**
 * @defgroup callback TEduBoardCallback
 * 白板功能的回调接口类
 */

/**
 * @defgroup def 关键类型定义
 */

/**
 * @defgroup code 错误码
 */

#ifdef __cplusplus
extern "C" {
#endif
    /// @name 创建销毁实例
    /// @{

    /**
     * @ingroup ctrl
     * @brief 创建白板控制类实例
     * @param disableCefInit                是否禁用CEF框架初始化，通常传默认值即可
     * @param cefRenderPath                 使用SDK内部的CEF初始化时，用于指定自定义Render进程可执行程序的路径，UTF8编码，为空或nullptr表示使用SDK内置Render进程
     * @return 白板控制类实例指针
     * @warning 该接口必须在主线程调用
     * @note 由于SDK基于CEF框架(BSD-licensed)实现，若您的程序中也使用了CEF框架，可能会存在冲突，我们为您提供了冲突解决方案：
     *      1. 选用以下两种方法中的一种来启用自己的Render进程
     *          - 令 disableCefInit = false，cefRenderPath 指向您自己的Render进程
     *          - 令 disableCefInit = true，自行实现CEF初始化
     *      2. 按下面说明，在您的Render进程内调用SDK的RenderProcessHandler
     *          - Render进程启动后调用接口获取一个sdkHandler实例，CefRefPtr<CefRenderProcessHandler> sdkHandler = (CefRenderProcessHandler*)GetTEduBoardRenderProcessHandler();
     *          - 在Render进程的CefApp中重写GetRenderProcessHandler方法，每次都返回以上sdkHandler
     *          - 若您需要自定义CefRenderProcessHandler，第二步可返回自定义Handler，然后在自定义Handler的下面几个方法中，调用sdkHandler的对应方法
     *              - OnBrowserCreated
     *              - OnBrowserDestroyed
     *              - OnContextCreated
     */
    EDUSDK_API TEduBoardController *CreateTEduBoardController(bool disableCefInit = false, const char *cefRenderPath = nullptr);

    /**
     * @ingroup ctrl
     * @brief 销毁白板控制类
     * @param ppBoardController	            指向白板控制类指针
     *
     * ppBoardController 指针会被自动置空
     */
    EDUSDK_API void DestroyTEduBoardController(TEduBoardController **ppBoardController);

    /// @}


    /// @name 日志相关接口
    /// @{

    /**
     * @ingroup ctrl
     * @brief 获取SDK版本号
     * @return SDK版本号
     *
     * 返回值内存由SDK内部管理，用户不需要自己释放
     */
    EDUSDK_API const char * GetTEduBoardVersion();

    /**
     * @ingroup ctrl
     * @brief 设置白板日志文件路径
     * @param logFilePath					要设置的白板日志文件路径，包含文件名及文件后缀，UTF8编码，为空或nullptr表示使用默认路径
     * @return 设置白板日志文件路径是否成功
     * @warning 该接口必须要在第一次调用CreateTEduBoardController之前调用才有效，否则将会失败
     *
     * - 默认路径，Windows下为："%AppData%\\..\\Local\TIC\\teduboard.log"
     * - 默认路径，Linux下为："~/TIC/teduboard.log"
     */
    EDUSDK_API bool SetTEduBoardLogFilePath(const char *logFilePath);

    /// @}

    /// @name 高级功能接口
    /// @{

    /**
     * @ingroup ctrl
     * @brief 启用白板离屏渲染
     * @return 启用离屏渲染是否成功
     * @warning 该接口必须要在第一次调用CreateTEduBoardController之前调用才有效，否则将会失败
     *
     * 启用离屏渲染时，SDK不再创建白板VIEW，而是通过onTEBOffscreenPaint回调接口将白板离屏渲染的像素数据抛出
     */
    EDUSDK_API bool EnableTEduBoardOffscreenRender();

    /**
     * @ingroup ctrl
     * @brief 获取SDK内部的CefRenderProcessHandler
     * @return SDK内部的CefRenderProcessHandler
     * @see CreateTEduBoardController
     *
     * 本接口详细使用方法参见CreateTEduBoardController接口说明
     */
    EDUSDK_API void * GetTEduBoardRenderProcessHandler();

    /// @}

#ifdef __cplusplus
}
#endif

/**
 * @ingroup code
 * @brief 白板错误码（严重）
 */
enum TEduBoardErrorCode {
    TEDU_BOARD_ERROR_INIT				= 1,	///< 初始化失败
    TEDU_BOARD_ERROR_AUTH				= 2, 	///< 服务鉴权失败，请先购买服务
    TEDU_BOARD_ERROR_LOAD				= 3,	///< 文件加载失败
    TEDU_BOARD_ERROR_TIM_INVALID    	= 5,    ///< 腾讯云IMSDK不可用
    TEDU_BOARD_ERROR_HISTORYDATA		= 6,	///< 同步历史数据失败
    TEDU_BOARD_ERROR_RUNTIME			= 100,	///< 白板运行错误
    TEDU_BOARD_ERROR_OOM                = 101,  ///< 内存耗尽
};

/**
 * @ingroup code
 * @brief 白板错误码（警告）
 */
enum TEduBoardWarningCode {
    TEDU_BOARD_WARNING_SYNC_DATA_PARSE_FAILED       = 1,    ///< 接收到其他端的同步数据解析错误
    TEDU_BOARD_WARNING_TIM_SEND_MSG_FAILED          = 2,    ///< 腾讯云IMSDK发送消息失败
    TEDU_BOARD_WARNING_H5PPT_ALREADY_EXISTS			= 3,    ///< 要添加的H5PPT已存在
    TEDU_BOARD_WARNING_AUTO_RELOAD                  = 4,    ///< 白板发生异常自动重新加载
    TEDU_BOARD_WARNING_ILLEGAL_OPERATION            = 5,    ///< 白板历史数据加载完成之前禁止操作
    TEDU_BOARD_WARNING_H5FILE_ALREADY_EXISTS        = 6,    ///< 当要添加的H5File已存在时抛出该警告
    TEDU_BOARD_WARNING_VIDEO_ALREADY_EXISTS         = 7,    ///< 当要添加的视频已存在时抛出该警告
};

/**
 * @ingroup def
 * @brief 白板工具
 */
enum TEduBoardToolType {
    TEDU_BOARD_TOOL_TYPE_MOUSE			= 0,	///< 鼠标
    TEDU_BOARD_TOOL_TYPE_PEN			= 1,	///< 画笔
    TEDU_BOARD_TOOL_TYPE_ERASER			= 2,	///< 橡皮擦
    TEDU_BOARD_TOOL_TYPE_LASER			= 3,	///< 激光笔
    TEDU_BOARD_TOOL_TYPE_LINE			= 4,	///< 直线
    TEDU_BOARD_TOOL_TYPE_OVAL			= 5,	///< 空心椭圆
    TEDU_BOARD_TOOL_TYPE_RECT			= 6,	///< 空心矩形
    TEDU_BOARD_TOOL_TYPE_OVAL_SOLID		= 7,	///< 实心椭圆
    TEDU_BOARD_TOOL_TYPE_RECT_SOLID		= 8,	///< 实心矩形
    TEDU_BOARD_TOOL_TYPE_POINT_SELECT	= 9,	///< 点选工具
    TEDU_BOARD_TOOL_TYPE_RECT_SELECT    = 10,	///< 框选工具
    TEDU_BOARD_TOOL_TYPE_TEXT			= 11,	///< 文本工具
    TEDU_BOARD_TOOL_TYPE_ZOOM_DRAG		= 12,	///< 缩放移动白板工具
};

/**
 * @ingroup def
 * @brief 白板图片填充对齐模式
 * 
 * 当以宽度基准等比例放大，则居左和居右同居中对齐效果一致；当以高度基准等比例放大，则居顶和居底同居中对齐效果一致
 */
enum TEduBoardImageFitMode {
    TEDU_BOARD_IMAGE_FIT_MODE_CENTER	= 0,	///< 以宽度或者高度为基准居中对齐等比例放大
    TEDU_BOARD_IMAGE_FIT_MODE_LEFT		= 4,	///< 以宽度或者高度为基准左对齐等比例放大
    TEDU_BOARD_IMAGE_FIT_MODE_TOP		= 5,	///< 以宽度或者高度为基准顶对齐等比例放大
    TEDU_BOARD_IMAGE_FIT_MODE_RIGHT		= 6,	///< 以宽度或者高度为基准右对齐等比例放大
    TEDU_BOARD_IMAGE_FIT_MODE_BOTTOM	= 7,	///< 以宽度或者高度为基准底对齐等比例放大
};

/**
 * @ingroup def
 * @brief 白板图片状态
 */
enum TEduBoardImageStatus {
    TEDU_BOARD_IMAGE_STATUS_LOADING		= 1,	///< 背景图片正在加载
    TEDU_BOARD_IMAGE_STATUS_LOAD_DONE	= 2,	///< 背景图片加载完成
    TEDU_BOARD_IMAGE_STATUS_LOAD_ABORT	= 3,	///< 背景图片加载中断
    TEDU_BOARD_IMAGE_STATUS_LOAD_ERROR	= 4,	///< 背景图片加载错误
};

/**
 * @ingroup def
 * @brief 白板文本样式
 */
enum TEduBoardTextStyle{
    TEDU_BOARD_TEXT_STYLE_NORMAL		= 0,	///< 常规样式
    TEDU_BOARD_TEXT_STYLE_BOLD			= 1,	///< 粗体样式
    TEDU_BOARD_TEXT_STYLE_ITALIC		= 2,	///< 斜体样式
    TEDU_BOARD_TEXT_STYLE_BOLD_ITALIC	= 3,	///< 粗斜体样式
};

/**
 * @ingroup def
 * @brief 白板上传状态
 */
enum TEduBoardUploadStatus{
    TEDU_BOARD_UPLOAD_STATUS_SUCCEED	= 1,	///< 上传成功
    TEDU_BOARD_UPLOAD_STATUS_FAILED		= 2,	///< 上传失败
};

/**
 * @ingroup def
 * @brief H5背景状态
 */
enum TEduBoardBackgroundH5Status{
    TEDU_BOARD_BACKGROUND_H5_STATUS_LOADING        = 1,    ///< H5背景正在加载
    TEDU_BOARD_BACKGROUND_H5_STATUS_LOAD_FINISH    = 2,    ///< H5背景加载完成
};

/**
 * @ingroup def
 * @brief 白板内容自适应模式
 * 
 * 内容包括图片、文件、PPT动画
 */
enum TEduBoardContentFitMode {
    TEDU_BOARD_CONTENT_FIT_MODE_NONE 			= 0,		///< 不使用内容自适应，默认模式，不自动调整白板宽高比，内容等比例缩放居中显示，内容宽高<=白板宽高
    TEDU_BOARD_CONTENT_FIT_MODE_CENTER_INSIDE 	= 1,		///< 自动调整白板宽高比与内容一致，内容铺满白板，白板等比例缩放居中显示，白板宽高<=容器宽高
    TEDU_BOARD_CONTENT_FIT_MODE_CENTER_COVER 	= 2,		///< 自动调整白板宽高比与内容一致，内容铺满白板，白板等比例缩放居中显示，白板宽高>=容器宽高
};

/**
 * @ingroup def
 * @brief 直线类型
 */
enum TEduBoardLineType {
    TEDU_BOARD_LINE_TYPE_SOLID    = 1,    ///< 实线
    TEDU_BOARD_LINE_TYPE_DOTTED   = 2,    ///< 虚线
};

/**
 * @ingroup def
 * @brief 箭头类型
 */
enum TEduBoardArrowType {
    TEDU_BOARD_ARROW_TYPE_NONE 		= 1,	///< 无箭头
    TEDU_BOARD_ARROW_TYPE_NORMAL	= 2, 	///< 普通箭头
    TEDU_BOARD_ARROW_TYPE_SOLID 	= 3, 	///< 实心箭头
};

/**
 * @ingroup def
 * @brief 椭圆绘制模式
 */
enum TEduBoardOvalDrawMode {
    TEDU_BOARD_OVAL_DRAW_MODE_FIX_START     = 1,    ///< 固定起始点，起始点和终点的中点为圆心
    TEDU_BOARD_OVAL_DRAW_MODE_FIX_CENTER    = 2,    ///< 固定圆心，起始点为圆心
};

/**
 * @ingroup def
 * @brief 文件转码状态
 */
enum TEduBoardFileTranscodeStatus {
    TEDU_BOARD_FILE_TRANSCODE_ERROR         = 1,    ///< 转码错误
    TEDU_BOARD_FILE_TRANSCODE_UPLOADING     = 2,    ///< 文件上传中
    TEDU_BOARD_FILE_TRANSCODE_CREATED       = 3,    ///< 发起转码任务
    TEDU_BOARD_FILE_TRANSCODE_QUEUED        = 4,    ///< 排队中
    TEDU_BOARD_FILE_TRANSCODE_PROCESSING    = 5,    ///< 转码中
    TEDU_BOARD_FILE_TRANSCODE_FINISHED      = 6,    ///< 转码完成
};

/**
 * @ingroup def
 * @brief H5文件状态
*/
enum TEduBoardH5FileStatus {
    TEDU_BOARD_H5_FILE_STATUS_LOADING       = 1,    ///< 加载中
    TEDU_BOARD_H5_FILE_STATUS_LOADED        = 2,    ///< 加载完成
};

/**
 * @ingroup def
 * @brief 视频文件状态
*/
enum TEduBoardVideoStatus {
    TEDU_BOARD_VIDEO_STATUS_ERROR       = 1,    ///< 播放错误
    TEDU_BOARD_VIDEO_STATUS_LOADING     = 2,    ///< 加载中
    TEDU_BOARD_VIDEO_STATUS_LOADED      = 3,    ///< 加载完成
    TEDU_BOARD_VIDEO_STATUS_PLAYED      = 4,    ///< 开始播放
    TEDU_BOARD_VIDEO_STATUS_PLAYING     = 5,    ///< 播放中
    TEDU_BOARD_VIDEO_STATUS_PAUSED      = 6,    ///< 暂停
    TEDU_BOARD_VIDEO_STATUS_SEEKED      = 7,    ///< 跳转
    TEDU_BOARD_VIDEO_STATUS_ENDED       = 8,    ///< 结束
};

/**
 * @ingroup def
 * @brief 白板授权参数
 */
struct TEduBoardAuthParam {
    uint32_t sdkAppId;      ///< SDKAppID
    const char * userId;    ///< 用户ID
    const char * userSig;   ///< 用户签名

    TEduBoardAuthParam()
            : sdkAppId(0)
            , userId(nullptr)
            , userSig(nullptr)
    {

    }

    TEduBoardAuthParam(uint32_t sdkAppId, const char * userId, const char * userSig)
            : sdkAppId(sdkAppId)
            , userId(userId)
            , userSig(userSig)
    {

    }
};

/**
 * @ingroup def
 * @brief 颜色参数
 */
struct TEduBoardColor {
    uint8_t red = 0;        ///< 红色分量
    uint8_t green = 0;      ///< 绿色分量
    uint8_t blue = 0;       ///< 蓝色分量
    uint8_t alpha = 0;      ///< 透明分量

    TEduBoardColor()
            : red(0)
            , green(0)
            , blue(0)
            , alpha(0)
    {

    }

    TEduBoardColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
            : red(red)
            , green(green)
            , blue(blue)
            , alpha(alpha)
    {

    }
};

/**
 * @ingroup def
 * @brief 白板初始化参数
 */
struct TEduBoardInitParam {
    bool progressEnable;					///< 是否启用SDK内置Loading图标
    const char * ratio;                     ///< 默认白板宽高比（可传格式如“4:3”、“16:9”的字符串）
    bool drawEnable;                        ///< 是否允许涂鸦
    TEduBoardColor globalBackgroundColor;   ///< 全局背景色
    TEduBoardToolType toolType;			    ///< 白板工具
    TEduBoardColor brushColor;              ///< 画笔颜色
    uint32_t brushThin;						///< 画笔粗细
    TEduBoardColor textColor;               ///< 文本颜色
    uint32_t textSize;                      ///< 文本粗细
    TEduBoardTextStyle textStyle;           ///< 文本样式
    bool timSync;                           ///< 是否使用腾讯云IMSDK进行实时数据同步
    bool dataSyncEnable;					///< 是否启用数据同步，禁用后将导致本地白板操作不会被同步给远端
    uint32_t preloadDepth;					///< 图片预加载深度，默认值5，表示预加载当前页前后5页的图片
    double smoothLevel;						///< 笔迹平滑系数，默认0.1，范围 [0，1]
    TEduBoardContentFitMode contentFitMode; ///< 内容自适应模式
    const char * experimental;				///< 实验性参数集，字典类型JSON串

    TEduBoardInitParam()
            : progressEnable(false)
            , ratio("16:9")
            , drawEnable(true)
            , globalBackgroundColor(255, 255, 255, 255)
            , toolType(TEDU_BOARD_TOOL_TYPE_MOUSE)
            , brushColor(255, 0, 0, 255)
            , brushThin(100)
            , textColor(0, 0, 0, 255)
            , textSize(320)
            , textStyle(TEDU_BOARD_TEXT_STYLE_NORMAL)
            , timSync(true)
            , dataSyncEnable(true)
            , preloadDepth(5)
            , smoothLevel(0.1)
            , contentFitMode(TEDU_BOARD_CONTENT_FIT_MODE_NONE)
            , experimental(nullptr)
    {

    }
};

/**
 * @ingroup def
 * @brief 直线样式
 */
struct TEduBoardLineStyle {
    TEduBoardLineType lineType;			///< 直线类型
    TEduBoardArrowType startArrowType;	///< 起点箭头类型
    TEduBoardArrowType endArrowType; 	///< 终点肩头类型

    TEduBoardLineStyle()
            : lineType(TEDU_BOARD_LINE_TYPE_SOLID)
            , startArrowType(TEDU_BOARD_ARROW_TYPE_NONE)
            , endArrowType(TEDU_BOARD_ARROW_TYPE_NONE)
    {

    }
};

/**
 * @ingroup def
 * @brief 鼠标样式
 */
struct TEduBoardCursorIcon{
    const char *cursor; ///< 浏览器内置鼠标指针样式，可取值参考文档：https://developer.mozilla.org/zh-CN/docs/Web/CSS/cursor
    const char *url;    ///< 自定义鼠标指针样式的URL，格式限制参考文档：https://developer.mozilla.org/zh-CN/docs/Web/CSS/cursor/url
    uint32_t offsetX;   ///< 自定义鼠标指针样式的横行偏移
    uint32_t offsetY;   ///< 自定义鼠标指针样式的纵向偏移

    TEduBoardCursorIcon()
        : cursor("none")
        , url(nullptr)
        , offsetX(0)
        , offsetY(0)
    {

    }
};

/**
 * @ingroup def
 * @brief 文件转码参数
 */
struct TEduBoardTranscodeConfig {
    const char *minResolution;	        ///< 指定转码结果最小分辨率，可用于提高转码结果清晰度，格式如960x540，宽高用x分隔
    bool isStaticPPT;                   ///< 指定对于PPT文件是否启用静态转码（转为静态图片），默认转为H5动画（转码耗时较长）
    const char *thumbnailResolution;    ///< 指定为文件生成缩略图的分辨率，默认不生成缩略图（生成缩略图增加额外转码耗时），格式如200x200，宽高用x分隔

    TEduBoardTranscodeConfig()
            : minResolution(nullptr)
            , isStaticPPT(false)
            , thumbnailResolution(nullptr)
    {
    }
};

/**
 * @ingroup def
 * @brief 文件转码结果
 */
struct TEduBoardTranscodeFileResult {
    char taskId[32];                        ///< 任务ID
    TEduBoardFileTranscodeStatus status;    ///< 转码状态
    double progress;                        ///< 转码进度，取值范围 [0, 100]
    char title[256];		                ///< 文件标题
    char resolution[32];	                ///< 文件分辨率
    uint32_t pages;			                ///< 文件总页数
    char url[1024];	                        ///< 转码结果URL
    char thumbnailResolution[32];           ///< 为文件生成缩略图的分辨率
    char thumbnailUrl[1024];	            ///< 为文件生成缩略图URL

    TEduBoardTranscodeFileResult()
            : taskId()
            , status(TEDU_BOARD_FILE_TRANSCODE_CREATED)
            , progress(0)
            , title()
            , resolution()
            , pages(0)
            , url()
            , thumbnailResolution()
            , thumbnailUrl()
    {
    }
};

/**
 * @ingroup def
 * @brief 白板信息
 */
struct TEduBoardInfo {
    const char * boardId;		        ///< 白板ID
    const char * backgroundUrl;		    ///< 白板背景图或者背景H5页面的URL
    TEduBoardColor backgroundColor;     ///< 白板背景色

    TEduBoardInfo()
            : boardId(nullptr)
            , backgroundUrl(nullptr)
    {

    }

    TEduBoardInfo(const char * boardId, const char * backgroundUrl, TEduBoardColor backgroundColor)
            : boardId(boardId)
            , backgroundUrl(backgroundUrl)
            , backgroundColor(backgroundColor)
    {

    }
};

/**
 * @ingroup def
 * @brief 白板信息列表
 */
class TEduBoardInfoList {
protected:
    virtual ~TEduBoardInfoList() {};

public:
    /**
     * @brief 获取白板信息个数
     * @return 白板信息个数
     */
    virtual uint32_t GetCount() const = 0;

    /**
     * @brief 获取指定的白板信息
     * @param index 索引，取值范围 [0, 白板个数)
     * @return 白板信息
     */
    virtual TEduBoardInfo GetBoardInfo(uint32_t index) const = 0;
};

/**
 * @ingroup def
 * @brief 文件信息
 */
struct TEduBoardFileInfo {
    const char * fileId;						///< 文件ID
    const char * title;							///< 文件名
    const char * downloadUrl; 					///< 文件下载地址
    uint32_t pageIndex;							///< 文件当前显示的页数
    uint32_t pageCount;							///< 文件页数
    const TEduBoardInfoList *boardInfoList;		///< 白板信息列表

    TEduBoardFileInfo()
            : fileId(nullptr)
            , title(nullptr)
            , downloadUrl(nullptr)
            , pageIndex(0)
            , pageCount(0)
            , boardInfoList(nullptr)
    {

    }

    TEduBoardFileInfo(const char * fileId, const char * title, const char * downloadUrl, uint32_t pageIndex, uint32_t pageCount, TEduBoardInfoList *boardInfoList)
            : fileId(fileId)
            , title(title)
            , downloadUrl(downloadUrl)
            , pageIndex(pageIndex)
            , pageCount(pageCount)
            , boardInfoList(boardInfoList)
    {

    }
};

/**
 * @ingroup def
 * @brief 文件信息列表
 */
class TEduBoardFileInfoList {
protected:
    virtual ~TEduBoardFileInfoList() {};

public:
    /**
     * @brief 获取文件信息个数
     * @return 文件信息个数
     */
    virtual uint32_t GetCount() const = 0;

    /**
     * @brief 获取指定的文件信息
     * @param index 索引，取值范围 [0, 文件个数)
     * @return 文件信息
     */
    virtual TEduBoardFileInfo GetFileInfo(uint32_t index) const = 0;

    /**
     * @brief 释放文件信息列表
     * @warning 文件信息列表使用完之后，务必调用该接口以释放内存
     */
    virtual void Release() = 0;
};

/**
 * @ingroup def
 * @brief 字符串列表
 */
class TEduBoardStringList {
protected:
    virtual ~TEduBoardStringList() {};

public:
    /**
     * @brief 获取字符串个数
     * @return 字符串个数
     */
    virtual uint32_t GetCount() const = 0;

    /**
     * @brief 获取指定的字符串
     * @param index 索引，取值范围 [0, 字符串个数)
     * @return 字符串
     * @warning 返回值内存由SDK内部管理，不需要用户自行释放
     */
    virtual const char * GetString(uint32_t index) const = 0;

    /**
     * @brief 释放字符串列表
     * @warning 字符串列表使用完之后，务必调用该接口以释放内存
     */
    virtual void Release() = 0;
};


/**
 * @ingroup callback
 * @brief 白板事件回调接口
 */
struct TEduBoardCallback {
     /// @name 通用事件回调
     /// @{

     /**
      * @brief 白板错误回调
      * @param code				错误码，参见TEduBoardErrorCode定义
      * @param msg				错误信息，编码格式为UTF8
      * @see TEduBoardErrorCode
      */
    virtual void onTEBError(TEduBoardErrorCode code, const char *msg) = 0;

    /**
     * @brief 白板警告回调
     * @param code				错误码，参见TEduBoardWarningCode定义
     * @param msg				错误信息，编码格式为UTF8
     * @see TEduBoardWarningCode
     */
    virtual void onTEBWarning(TEduBoardWarningCode code, const char *msg) = 0;

    /// @}


    /// @name 基本流程回调
    /// @{

    /**
     * @brief 白板初始化完成回调
     *
     * 收到该回调后表示白板已处于可正常工作状态（此时白板为空白白板，历史数据尚未拉取到）
     */
    virtual void onTEBInit() = 0;

    /**
     * @brief 白板历史数据同步完成回调
     */
    virtual void onTEBHistroyDataSyncCompleted() {};

    /**
     * @brief 白板同步数据回调
     * @param data				白板同步数据（JSON格式字符串）
     *
     * 收到该回调时需要将回调数据通过信令通道发送给房间内其他人，接受者收到后调用AddSyncData接口将数据添加到白板以实现数据同步
     * 该回调用于多个白板间的数据同步，使用腾讯云IMSDK进行实时数据同步时，不会收到该回调
     */
    virtual void onTEBSyncData(const char *data) {};

    /**
     * @brief 白板可撤销状态改变回调
     * @param canUndo			白板当前是否还能执行Undo操作
     */
    virtual void onTEBUndoStatusChanged(bool canUndo) {};

    /**
     * @brief 白板可重做状态改变回调
     * @param canRedo			白板当前是否还能执行Redo操作
     */
    virtual void onTEBRedoStatusChanged(bool canRedo) {};

    /**
     * @brief 白板离屏渲染回调
     * @param buffer            白板像素数据，大小为width * height * 4，像素以白板左上方为原点从左到右从上到下按BGRA排列
     * @param width             白板像素数据的宽度
     * @param height            白板像素数据的高度
     *
     * 该回调只有在启用离屏渲染时才会被触发
     */
    virtual void onTEBOffscreenPaint(const void* buffer, uint32_t width, uint32_t height) {};

    /// @}


    /// @name 涂鸦功能回调
    /// @{

     /**
      * @brief 白板图片状态改变回调
      * @param boardId			白板ID
      * @param url				白板图片URL
      * @param status			新的白板图片状态
      */
    virtual void onTEBImageStatusChanged(const char *boardId, const char *url, TEduBoardImageStatus status) {};

    /**
     * @brief 设置白板背景图片回调
     * @param url				调用SetBackgroundImage时传入的URL
     *
     * 只有本地调用SetBackgroundImage时会收到该回调
     * 收到该回调表示背景图片已经上传或下载成功，并且显示出来
     */
    virtual void onTEBSetBackgroundImage(const char *url) {};

    /**
     * @brief 设置白板背景H5状态改变回调
     * @param boardId           白板ID
     * @param url               白板图片URL
     * @param status            新的白板图片状态
     */
    virtual void onTEBBackgroundH5StatusChanged(const char *boardId, const char *url, TEduBoardBackgroundH5Status status) {};

    /// @}


    /// @name 白板页操作回调
    /// @{

    /**
     * @brief 增加白板页回调
     * @param boardList		增加的白板页ID列表（使用后不需要自行调用Release方法释放，SDK内部自动释放）
     * @param fileId			增加的白板页所属的文件ID（目前版本只可能为#DEFAULT）
     */
    virtual void onTEBAddBoard(const TEduBoardStringList *boardList, const char *fileId) {};

    /**
     * @brief 删除白板页回调
     * @param boardList			删除的白板页ID（使用后不需要自行调用Release方法释放，SDK内部自动释放）
     * @param fileId			删除的白板页所属的文件ID（目前版本只可能为#DEFAULT）
     */
    virtual void onTEBDeleteBoard(const TEduBoardStringList *boardList, const char *fileId) {};

    /**
     * @brief 跳转白板页回调
     * @param boardId			跳转到的白板页ID
     * @param fileId			跳转到的白板页所属的文件ID
     */
    virtual void onTEBGotoBoard(const char *boardId, const char *fileId) {};

    /**
     * @brief 白板页动画步数回调
     * @param currentStep		当前白板页动画步数，取值范围 [0, totalStep)
     * @param totalStep			当前白板页动画总步数
     */
    virtual void onTEBGotoStep(uint32_t currentStep, uint32_t totalStep) {};

    /// @}


    /// @name 文件操作回调
    /// @{

    /**
     * @brief 文件转码进度回调
     * @param path              正在转码的本地文件路径
     * @param errorCode         文件转码错误码，无异常时为空字符串 ""
     * @param errorMsg          文件转码错误信息，无异常时为空字符串 ""
     * @param result            文件转码结果
     */
    virtual void onTEBFileTranscodeProgress(const char *path, const char *errorCode, const char *errorMsg, const TEduBoardTranscodeFileResult &result) {};

    /**
     * @brief 增加转码文件回调
     * @param fileId			增加的文件ID
     *
     * 文件加载完成后才会触发该回调
     */
    virtual void onTEBAddTranscodeFile(const char *fileId) {};

    /**
     * @brief 视频文件状态回调
     * @param fileId            文件ID
     * @param status            文件状态
     * @param progress          当前进度（秒）（仅支持mp4格式）
     * @param duration          总时长（秒）（仅支持mp4格式）
     */
    virtual void onTEBVideoStatusChanged(const char *fileId, TEduBoardVideoStatus status, double progress, double duration) {};

    /**
     * @brief H5文件状态回调
     * @param fileId            文件ID
     * @param status            文件状态
     */
    virtual void onTEBH5FileStatusChanged(const char *fileId, TEduBoardH5FileStatus status) {};

    /**
     * @brief 删除文件回调
     * @param fileId			删除的文件ID
     */
    virtual void onTEBDeleteFile(const char *fileId) {};

    /**
     * @brief 切换文件回调
     * @param fileId			切换到的文件ID
     */
    virtual void onTEBSwitchFile(const char *fileId) {};

    /**
     * @brief 文件上传进度回调
     * @param fileId            正在上传的文件ID
     * @param currentBytes      当前已上传大小，单位bytes
     * @param totalBytes        文件总大小，单位bytes
     * @param uploadSpeed       文件上传速度，单位bytes
     * @param percent			文件上传进度，取值范围 [0, 1]
     */
    virtual void onTEBFileUploadProgress(const char *fileId, int currentBytes, int totalBytes, int uploadSpeed, double percent) {};

    /**
     * @brief 文件上传状态回调
     * @param fileId            正在上传的文件ID
     * @param status            文件上传状态
     * @param errorCode			文件上传错误码
     * @param errorMsg			文件上传错误信息
     */
    virtual void onTEBFileUploadStatus(const char *fileId, TEduBoardUploadStatus status, int errorCode, const char *errorMsg) {};

    /// @}

};


/**
 * @ingroup ctrl
 * @brief 白板控制器
 */
class TEduBoardController {
protected:
    virtual ~TEduBoardController() {};

public:
    /// @name 设置 TEduBoardCallback 回调
    /// @{

    /**
     * @brief 设置事件回调监听
     * @param callback 			事件回调监听
     * @warning 建议在Init之前调用该方法以支持错误处理
     */
    virtual void AddCallback(TEduBoardCallback * callback) = 0;

    /**
     * @brief 删除事件回调监听
     * @param callback 			事件回调监听
     */
    virtual void RemoveCallback(TEduBoardCallback *callback) = 0;

    /// @}


    /// @name 基本流程接口
    /// @{

    /**
     * @brief 初始化白板
     * @param authParam 		授权参数
     * @param roomId 			课堂ID
     * @param initParam	 	 	可选参数，指定用于初始化白板的一系列属性值
     * @warning 使用腾讯云IMSDK进行实时数据同步时，只支持一个白板实例，创建多个白板实例可能导致涂鸦状态异常
     * 
     * 可用 initParam.timSync 指定是否使用腾讯云IMSDK进行实时数据同步
     * initParam.timSync == true 时，会尝试反射调用腾讯云IMSDK作为信令通道进行实时数据收发（只实现消息收发，初始化、进房等操作需要用户自行实现），目前仅支持IMSDK 4.3.118及以上版本
     */
    virtual void Init(const TEduBoardAuthParam & authParam, uint32_t roomId, const TEduBoardInitParam &initParam = TEduBoardInitParam()) = 0;

    /**
     * @brief 获取白板渲染View
     * @return 白板渲染View
     */
    virtual WINDOW_HANDLE GetBoardRenderView() = 0;

    /**
     * @brief 添加白板同步数据
     * @param data 				接收到的房间内其他人发送的同步数据
     *
     * 该接口用于多个白板间的数据同步，使用内置IM作为信令通道时，不需要调用该接口
     */
    virtual void AddSyncData(const char * data) = 0;

    /**
     * @brief 设置白板是否开启数据同步
     * @param enable    是否开启
     *
     * 白板创建后默认开启数据同步，关闭数据同步，本地的所有白板操作不会同步到远端和服务器
     */
    virtual void SetDataSyncEnable(bool enable) = 0;

    /**
     * @brief 获取白板是否开启数据同步
     * @return 是否开启数据同步，true 表示开启，false 表示关闭
     */
    virtual bool IsDataSyncEnable() = 0;

    /**
     * @brief 重置白板
     * 
     * 调用该接口后将会删除所有的白板页和文件
     */
    virtual void Reset() = 0;

    /**
     * @brief 设置白板渲染View的位置和大小
     * @param x                 要设置的白板渲染View的位置X分量
     * @param y                 要设置的白板渲染View的位置Y分量
     * @param width             要设置的白板渲染View的宽度
     * @param height            要设置的白板渲染View的高度
     * 
     * 白板渲染View有父窗口时，(x, y) 指定相对其父窗口的位置
     */
    virtual void SetBoardRenderViewPos(int32_t x, int32_t y, uint32_t width, uint32_t height) = 0;

    /**
     * @brief 获取同步时间戳
     * @return 毫秒级同步时间戳
     */
    virtual uint64_t GetSyncTime() = 0;

    /**
     * @brief 同步远端时间戳
     * @param userId			远端用户ID
     * @param timestamp			远端用户毫秒级同步时间戳
     */
    virtual void SyncRemoteTime(const char *userId, uint64_t timestamp) = 0;

    /**
     * @brief 调用白板实验性接口
     * @param apiExp			要执行的白板相关JS代码
     * @return JS执行后的返回值转换而来的字符串
     */
    virtual const char * CallExperimentalAPI(const char * apiExp) = 0;

    /// @}


    /// @name 涂鸦相关接口
    /// @{

    /**
     * @brief 设置白板是否允许涂鸦
     * @param enable 			是否允许涂鸦，true 表示白板可以涂鸦，false 表示白板不能涂鸦
     *
     * 白板创建后默认为允许涂鸦状态
     */
    virtual void SetDrawEnable(bool enable) = 0;

    /**
     * @brief 获取白板是否允许涂鸦
     * @return 是否允许涂鸦，true 表示白板可以涂鸦，false 表示白板不能涂鸦
     */
    virtual bool IsDrawEnable() = 0;

    /**
     * @brief 设置允许操作哪些用户绘制的图形
     * @param users             指定允许操作的用户集，为nullptr表示不加限制
     * @param userCount         指定users参数包含的用户个数
     * 
     * 该接口会产生以下影响：
     *    1. ERASER 工具只能擦除users参数列出的用户绘制的涂鸦，无法擦除其他人绘制的涂鸦
     *    2. POINTSELECT、SELECT 工具只能选中users参数列出的用户绘制的涂鸦，无法选中其他人绘制的涂鸦
     *    3. clear 接口只能用于清空选中涂鸦以及users参数列出的用户绘制的涂鸦，无法清空背景及其他人绘制的涂鸦
     *    4. 白板包含的其他功能未在本列表明确列出者都可以确定不受本接口影响
     */
    virtual void SetAccessibleUsers(const char **users, uint32_t userCount) = 0;

    /**
     * @brief 设置所有白板的背景色
     * @param color 			要设置的全局背景色
     * 
     * 调用该接口将导致所有白板的背景色发生改变
     * 新创建白板的默认背景色取全局背景色
     */
    virtual void SetGlobalBackgroundColor(const TEduBoardColor &color) = 0;

    /**
     * @brief 获取白板全局背景色
     * @return 全局背景色
     */
    virtual TEduBoardColor GetGlobalBackgroundColor() = 0;

    /**
     * @brief 设置当前白板页的背景色
     * @param color 			要设置的背景色
     *
     * 白板页创建以后的默认背景色由SetDefaultBackgroundColor接口设定
     */
    virtual void SetBackgroundColor(const TEduBoardColor & color) = 0;

    /**
     * @brief 获取当前白板页的背景色
     * @return 当前白板页的背景色
     */
    virtual TEduBoardColor GetBackgroundColor() = 0;

    /**
     * @brief 设置要使用的白板工具
     * @param type 				要设置的白板工具
     */
    virtual void SetToolType(TEduBoardToolType type) = 0;

    /**
     * @brief 获取正在使用的白板工具
     * @return 正在使用的白板工具
     */
    virtual TEduBoardToolType GetToolType() = 0;

    /**
     * @brief 自定义白板工具鼠标样式
     * @param type              要设置鼠标样式的白板工具类型
     * @param icon              要设置的鼠标样式
     */
    virtual void SetCursorIcon(TEduBoardToolType type, const TEduBoardCursorIcon &icon) = 0;

    /**
     * @brief 设置画笔颜色
     * @param color 			要设置的画笔颜色
     *
     * 画笔颜色用于所有涂鸦绘制
     */
    virtual void SetBrushColor(const TEduBoardColor & color) = 0;

    /**
     * @brief 获取画笔颜色
     * @return 画笔颜色
     */
    virtual TEduBoardColor GetBrushColor() = 0;

    /**
     * @brief 设置画笔粗细
     * @param thin 				要设置的画笔粗细
     *
     * 画笔粗细用于所有涂鸦绘制，实际像素值取值(thin * 白板的高度 / 10000)px，如果结果小于1px，则涂鸦的线条会比较虚
     */
    virtual void SetBrushThin(uint32_t thin) = 0;

    /**
     * @brief 获取画笔粗细
     * @return 画笔粗细
     */
    virtual uint32_t GetBrushThin() = 0;

    /**
     * @brief 设置文本颜色
     * @param color 			要设置的文本颜色
     */
    virtual void SetTextColor(const TEduBoardColor & color) = 0;

    /**
     * @brief 获取文本颜色
     * @return 文本颜色
     */
    virtual TEduBoardColor GetTextColor() = 0;

    /**
     * @brief 设置文本大小
     * @param size 				要设置的文本大小
     *
     * 实际像素值取值(size * 白板的高度 / 10000)px
     */
    virtual void SetTextSize(uint32_t size) = 0;

    /**
     * @brief 获取文本大小
     * @return 文本大小
     */
    virtual uint32_t GetTextSize() = 0;

    /**
     * @brief 设置文本样式
     * @param style 			要设置的文本样式
     */
    virtual void SetTextStyle(TEduBoardTextStyle style) = 0;

    /**
     * @brief 获取文本样式
     * @return 文本样式
     */
    virtual TEduBoardTextStyle GetTextStyle() = 0;

    /**
     * @brief 设置直线样式
     * @param style 			要设置的直线样式
     */
    virtual void SetLineStyle(const TEduBoardLineStyle & style) = 0;

    /**
     * @brief 获取直线样式
     * @return 直线样式
     */
    virtual TEduBoardLineStyle GetLineStyle() = 0;

    /**
     * @brief 设置椭圆绘制模式
     * @param drawMode 			要设置的椭圆绘制模式
     */
    virtual void SetOvalDrawMode(TEduBoardOvalDrawMode drawMode) = 0;

    /**
     * @brief 获取椭圆绘制模式
     * @return 椭圆绘制模式
     */
    virtual TEduBoardOvalDrawMode GetOvalDrawMode() = 0;

    /**
     * @brief 清空当前白板页涂鸦
     * @param clearBackground 	是否同时清空背景色以及背景图片
     * @param clearSelectedOnly 是否只清除选中部分涂鸦
     * @warning 目前不支持清除选中部分的同时清除背景
     */
    virtual void Clear(bool clearBackground = false, bool clearSelectedOnly = false) = 0;

    /**
     * @brief 设置当前白板页的背景图片
     * @param url 				要设置的背景图片URL，编码格式为UTF8
     * @param mode				要使用的图片填充对齐模式
     * 
     * 当URL是一个有效的本地文件地址时，该文件会被自动上传到COS
     */
    virtual void SetBackgroundImage(const char * url, TEduBoardImageFitMode mode) = 0;

    /**
     * @brief 设置当前白板页的背景H5页面
     * @param url				要设置的背景H5页面URL
     *
     * 该接口与SetBackgroundImage接口互斥
     */
    virtual void SetBackgroundH5(const char * url) = 0;

    /**
     * @brief 撤销当前白板页上一次动作
     */
    virtual void Undo() = 0;

    /**
     * @brief 重做当前白板页上一次撤销
     */
    virtual void Redo() = 0;

    /// @}


    /// @name 白板页操作接口
    /// @{

    /**
     * @brief 增加一页白板
     * @param url				要使用的背景图片URL，编码格式为UTF8，为nullptr表示不指定背景图片
     * @return 白板ID
     * @warning 白板页会被添加到默认文件（文件ID为#DEFAULT)，自行上传的文件无法添加白板页
     *
     * 返回值内存由SDK内部管理，用户不需要自己释放
     */
    virtual const char * AddBoard(const char * url = nullptr) = 0;

    /**
     * @brief 添加图片资源
     * @param url               要添加的图片元素URL地址，编码格式为UTF8
     */
    virtual void AddImageElement(const char * url) = 0;

    /**
     * @brief 删除一页白板
     * @param boardId			要删除的白板ID，为nullptr表示删除当前页
     * @warning 只允许删除默认文件（文件ID为#DEFAULT）内的白板页，且默认白板页（白板ID为#DEFAULT）无法删除
     */
    virtual void DeleteBoard(const char * boardId = nullptr) = 0;

    /**
     * @brief 上一步
     *  每个Step对应PPT的一个动画效果，若当前没有已展示的动画效果，则该接口调用会导致向前翻页
     */
    virtual void PrevStep() = 0;

    /**
     * @brief 下一步
     * 
     * 每个Step对应PPT的一个动画效果，若当前没有未展示的动画效果，则该接口调用会导致向后翻页
     */
    virtual void NextStep() = 0;

    /**
     * @brief 向前翻页
     * @param resetStep			指定翻到指定页以后是否重置PPT动画步数
     *
     * 若当前白板页为当前文件的第一页，则该接口调用无效
     */
    virtual void PrevBoard(bool resetStep = false) = 0;

    /**
     * @brief 向后翻页
     * @param resetStep			指定翻到指定页以后是否重置PPT动画步数
     *
     * 若当前白板页为当前文件的最后一页，则该接口调用无效
     */
    virtual void NextBoard(bool resetStep = false) = 0;

    /**
     * @brief 跳转到指定白板页
     * @param boardId			要跳转到的白板页ID
     * @param resetStep			指定翻到指定页以后是否重置PPT动画步数
     *
     * 允许跳转到任意文件的白板页
     */
    virtual void GotoBoard(const char * boardId, bool resetStep = false) = 0;

    /**
     * @brief 获取当前白板页ID
     * @return 当前白板页ID
     *
     * 返回值内存由SDK内部管理，用户不需要自己释放
     */
    virtual const char * GetCurrentBoard() = 0;

    /**
     * @brief 获取所有文件的白板列表
     * @return 所有文件的白板列表
     * @warning 返回值不再使用时不需要自行delete，但是务必调用其release方法以释放内存占用
     */
    virtual TEduBoardStringList *GetBoardList() = 0;

    /**
     * @brief 设置当前白板页宽高比
     * @param ratio				要设置的白板宽高比
     *
     * 格式如: "4:3"、"16:9"
     */
    virtual void SetBoardRatio(const char *ratio) = 0;

    /**
     * @brief 获取当前白板页宽高比
     * @return 白板宽高比，格式与SetBoardRatio接口参数格式一致
     */
    virtual const char * GetBoardRatio() = 0;

    /**
     * @brief 设置当前白板页缩放比例
     * @param scale				要设置的白板缩放比例
     *
     * 支持范围: [100，300]，实际缩放比为: scale/100
     */
    virtual void SetBoardScale(uint32_t scale) = 0;

    /**
     * @brief 获取当前白板页缩放比例
     * @return 白板缩放比例，格式与SetBoardScale接口参数格式一致
     */
    virtual uint32_t GetBoardScale() = 0;

    /**
     * @brief 设置白板内容自适应模式
     * @param mode				要设置的白板内容自适应模式
     *
     * 设置自适应模式后会影响所有后续白板内容操作,受影响接口包括：AddTranscodeFile
     */
    virtual void SetBoardContentFitMode(TEduBoardContentFitMode mode) = 0;

    /**
     * @brief 获取白板内容自适应模式
     * @return 白板内容自适应模式
     */
    virtual TEduBoardContentFitMode GetBoardContentFitMode() = 0;

    /// @}


    /// @name 文件操作接口
    /// @{

    /**
     * @brief 发起文件转码请求
     * @param path				要转码的文件路径，编码格式为UTF8
     * @param config            转码参数
     * @warning 本接口设计用于在接入阶段快速体验转码功能，原则上不建议在生产环境中使用，生产环境中的转码请求建议使用后台服务接口发起
     * @see TEduBoardCallback::onTEBFileTranscodeProgress
     *
     * 支持 PPT、PDF、Word文件转码
     * PPT文档默认转为H5动画，能够还原PPT原有动画效果，其它文档转码为静态图片
     * PPT动画转码耗时约1秒/页，所有文档的静态转码耗时约0.5秒/页
     * 转码进度和结果将会通过onTEBFileTranscodeProgress回调返回，详情参见该回调说明文档
     */
    virtual void ApplyFileTranscode(const char * path, const TEduBoardTranscodeConfig &config = TEduBoardTranscodeConfig()) = 0;

    /**
     * @brief 主动查询文件转码进度
     * @param taskId            通过onTEBFileTranscodeProgress回调拿到的转码任务taskId
     * @warning 该接口仅用于特殊业务场景下主动查询文件转码进度，调用ApplyFileTranscode后，SDK内部将会自动定期触发onTEBFileTranscodeProgress回调，正常情况下您不需要主动调用此接口
     * @see TEduBoardCallback::onTEBFileTranscodeProgress
     * 
     * 转码进度和结果将会通过onTEBFileTranscodeProgress回调返回，详情参见该回调说明文档
     */
    virtual void GetFileTranscodeProgress(const char *taskId) = 0;

    /**
     * @brief 添加转码文件
     * @param  result 			文件转码结果
     * @return 文件ID
     * @warning 当传入文件的URL重复时，文件ID返回为空字符串
     * @warning 在收到对应的onTEBAddTranscodeFile回调前，无法用返回的文件ID查询到文件信息
     * @see TEduBoardCallback::onTEBAddTranscodeFile
     *
     * 本接口只处理传入参数结构体的title、resolution、url、pages字段
     * 调用该接口后，SDK会在后台进行文件加载，期间用户可正常进行其它操作，加载成功或失败后会触发相应回调
     * 文件加载成功后，将自动切换到该文件
     */
    virtual const char * AddTranscodeFile(const TEduBoardTranscodeFileResult & result) = 0;

    /**
     * @brief 添加视频文件
     * @param url               文件播放地址
     * @return 文件ID
     *
     * 移动端支持mp4/m3u8，桌面端支持mp4/m3u8/flv/rtmp；触发状态改变回调 onTEBVideoStatusChange
     */
    virtual const char *AddVideoFile(const char *url) = 0;

    /**
     * @brief 显示或隐藏视频控制栏
     * @param show        是否显示
     * @warning 全局控制项，对所有视频文件有效
     * 隐藏和显示默认视频控制栏，默认显示系统自带的video控制栏，不同平台界面UI样式不同
     */
    virtual void ShowVideoControl(bool show) = 0;

    /**
     * @brief 播放视频
     * @warning 只对当前文件有效
     *
     * 触发状态改变回调 onTEBVideoStatusChange，一般在使用自定义视频控制栏时使用
     */
    virtual void PlayVideo() = 0;

    /**
     * @brief 暂停视频
     * @warning 只对当前文件有效
     *
     * 触发状态改变回调 onTEBVideoStatusChange，一般在使用自定义视频控制栏时使用
     */
    virtual void PauseVideo() = 0;

    /**
     * @brief 跳转（仅支持点播视频）
     * @param time              播放进度，单位秒
     * @warning 只对当前文件有效
     *
     * 触发状态改变回调 onTEBVideoStatusChange，一般在使用自定义视频控制栏时使用
     */
    virtual void SeekVideo(double time) = 0;

    /**
     * @brief 是否同步本地视频操作到远端
     * @param enable            是否同步
     * @warning 全局控制项，对所有视频文件有效
     *
     * play/pause/seek接口以及控制栏事件的触发是否影响远端，默认为true
     * 一般情况下学生设置为false，老师设置为true
     */
    virtual void SetSyncVideoStatusEnable(bool enable) = 0;

    /**
     * @brief 内部启动定时器，定时同步视频状态到远端（仅限于mp4）
     * @param interval          同步间隔，例如设置5秒
     * @warning 只对当前文件有效
     *
     * 一般在老师端视频加载完成后调用，切换文件后内部自动销毁定时器，
     */
    virtual void StartSyncVideoStatus(uint32_t interval) = 0;

    /**
     * @brief 停止同步视频状态
     * @warning 只对当前文件有效
     */
    virtual void StopSyncVideoStatus() = 0;

    /**
     * @brief 添加H5页面
     * @note 只支持展示，不支持互动
     * @param url               网页地址
     * @return 文件ID
     */
    virtual const char *AddH5File(const char *url) = 0;

    /**
     * @brief 删除文件
     * @param fileId			要删除的文件ID
     *
     * 文件ID为nullptr时表示当前文件，默认文件无法删除
     */
    virtual void DeleteFile(const char * fileId) = 0;

    /**
     * @brief 切换文件
     * @param fileId			要切换到的文件ID
     * @param boardId           切换文件并跳转到这个白板页
     * @param stepIndex         跳转到白板页并切换到这个动画
     * @warning 该接口仅可用于文件切换，如果传入的fileId为当前文件ID，SDK会忽略其它参数，不做任何操作
     * @note 文件ID为必填项，为nullptr或空字符串将导致文件切换失败
     */
    virtual void SwitchFile(const char * fileId, const char *boardId = nullptr, int32_t stepIndex = -1) = 0;

    /**
     * @brief 获取当前文件ID
     * @return 当前文件ID
     */
    virtual const char * GetCurrentFile() = 0;

    /**
     * @brief 获取白板中指定文件的文件信息
     * @return 文件信息
     * @warning 每次调用该接口的返回值内容都指向同一块内存，若需要保存返回信息，请在拿到返回值后及时拷贝走
     */
    virtual TEduBoardFileInfo GetFileInfo(const char *fileId) = 0;

    /**
     * @brief 获取白板中上传的所有文件的文件信息列表
     * @return 文件信息列表
     * @warning 返回值不再使用时不需要自行delete，但是务必调用其release方法以释放内存占用
     */
    virtual TEduBoardFileInfoList * GetFileInfoList() = 0;

    /**
     * @brief 获取指定文件的白板ID列表
     * @param fileId			文件ID
     * @return 白板ID列表
     * @warning 返回值不再使用时不需要自行delete，但是务必调用其release方法以释放内存占用
     */
    virtual TEduBoardStringList * GetFileBoardList(const char * fileId) = 0;

    /**
     * @brief 获取指定文件的缩略图，不支持默认文件（fileId=#DEFAULT）
     * @param fileId        	文件ID
     * @return 缩略图URL列表
     * @note 用户在调用rest api请求转码时，需要带上 "thumbnail_resolution" 参数，开启缩略图功能，否则返回的缩略图url无效
     */
    virtual TEduBoardStringList * GetThumbnailImages(const char * fileId) = 0;

    /**
     * @brief 清空指定文件的所有白板涂鸦
     * @param fileId			文件ID
     */
    virtual void ClearFileDraws(const char * fileId) = 0;

    /// @}
};
