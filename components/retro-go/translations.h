#include "rg_localization.h"

static const char *language_names[RG_LANG_MAX] = {
    [RG_LANG_EN] = "English",
    [RG_LANG_ZH] = "中文",
};

static const char *translations[][RG_LANG_MAX] =
{
    {
        [RG_LANG_EN] = "Never",
        [RG_LANG_ZH] = "从不"
    },
    {
        [RG_LANG_EN] = "Always",
        [RG_LANG_ZH] = "始终"
    },
    {
        [RG_LANG_EN] = "Composite",
        [RG_LANG_ZH] = "复合"
    },
    {
        [RG_LANG_EN] = "NES Classic",
        [RG_LANG_ZH] = "NES经典"
    },
    {
        [RG_LANG_EN] = "NTSC",
        [RG_LANG_ZH] = "NTSC"
    },
    {
        [RG_LANG_EN] = "PVM",
        [RG_LANG_ZH] = "PVM"
    },
    {
        [RG_LANG_EN] = "Smooth",
        [RG_LANG_ZH] = "平滑"
    },
    {
        [RG_LANG_EN] = "To start, try: 1 or * or #",
        [RG_LANG_ZH] = "开始请按: 1 或 * 或 #"
    },
    {
	    [RG_LANG_EN] = "Full",
	    [RG_LANG_ZH] = "全屏"
    },
    {
        [RG_LANG_EN] = "Yes",
        [RG_LANG_ZH] = "是"
    },
    {
        [RG_LANG_EN] = "Select file",
        [RG_LANG_ZH] = "选择文件"
    },
    {
        [RG_LANG_EN] = "Language",
        [RG_LANG_ZH] = "语言"
    },
    {
        [RG_LANG_EN] = "Language changed!",
        [RG_LANG_ZH] = "语言已更改！"
    },
    {
        [RG_LANG_EN] = "For these changes to take effect you must restart your device.\nrestart now?",
        [RG_LANG_ZH] = "这些更改需要重启才能生效。\n现在重启？"
    },
    {
        [RG_LANG_EN] = "Wi-Fi profile",
        [RG_LANG_ZH] = "Wi-Fi配置"
    },
    {
        [RG_LANG_EN] = "Language",
        [RG_LANG_ZH] = "语言"
    },
    {
        [RG_LANG_EN] = "Options",
        [RG_LANG_ZH] = "选项"
    },
    {
        [RG_LANG_EN] = "About Retro-Go",
        [RG_LANG_ZH] = "关于Retro-Go"
    },
    {
        [RG_LANG_EN] = "Reset all settings?",
        [RG_LANG_ZH] = "重置所有设置？"
    },
    {
        [RG_LANG_EN] = "Initializing...",
        [RG_LANG_ZH] = "初始化中..."
    },
    {
        [RG_LANG_EN] = "Host Game (P1)",
        [RG_LANG_ZH] = "托管游戏 (P1)",
    },
    {
        [RG_LANG_EN] = "Find Game (P2)",
        [RG_LANG_ZH] = "查找游戏(P2)"
    },
    {
        [RG_LANG_EN] = "Netplay",
        [RG_LANG_ZH] = "网络对战"
    },
    {
        [RG_LANG_EN] = "ROMs not identical. Continue?",
        [RG_LANG_ZH] = "ROM不一致，继续？"
    },
    {
        [RG_LANG_EN] = "Exchanging info...",
        [RG_LANG_ZH] = "交换信息中..."
    },
    {
        [RG_LANG_EN] = "Unable to find host!",
        [RG_LANG_ZH] = "未找到主机！"
    },
    {
        [RG_LANG_EN] = "Connection failed!",
        [RG_LANG_ZH] = "连接失败！"
    },
    {
        [RG_LANG_EN] = "Waiting for peer...",
        [RG_LANG_ZH] = "等待对方..."
    },
    {
        [RG_LANG_EN] = "Unknown status...",
        [RG_LANG_ZH] = "未知状态..."
    },
    {
        [RG_LANG_EN] = "On",
        [RG_LANG_ZH] = "开"
    },
    {
        [RG_LANG_EN] = "Keyboard",
        [RG_LANG_ZH] = "键盘"
    },
    {
        [RG_LANG_EN] = "Joystick",
        [RG_LANG_ZH] = "摇杆"
    },
    {
        [RG_LANG_EN] = "Input",
        [RG_LANG_ZH] = "输入"
    },
    {
        [RG_LANG_EN] = "Crop",
        [RG_LANG_ZH] = "裁剪"
    },
    {
        [RG_LANG_EN] = "BIOS file missing!",
        [RG_LANG_ZH] = "缺少BIOS文件！"
    },
    {
        [RG_LANG_EN] = "YM2612 audio ",
        [RG_LANG_ZH] = "YM2612音频 "
    },
    {
        [RG_LANG_EN] = "SN76489 audio",
        [RG_LANG_ZH] = "SN76489音频"
    },
    {
        [RG_LANG_EN] = "Z80 emulation",
        [RG_LANG_ZH] = "Z80模拟"
    },
    {
        [RG_LANG_EN] = "Launcher options",
        [RG_LANG_ZH] = "启动器选项"
    },
    {
        [RG_LANG_EN] = "Emulator options",
        [RG_LANG_ZH] = "模拟器选项"
    },
    {
        [RG_LANG_EN] = "Date",
        [RG_LANG_ZH] = "日期"
    },
    {
        [RG_LANG_EN] = "Files:",
        [RG_LANG_ZH] = "文件："
    },
    {
        [RG_LANG_EN] = "Download complete!",
        [RG_LANG_ZH] = "下载完成！"
    },
    {
        [RG_LANG_EN] = "Reboot to flash?",
        [RG_LANG_ZH] = "重启刷写？"
    },
    {
        [RG_LANG_EN] = "Available Releases",
        [RG_LANG_ZH] = "可用版本"
    },
    {
        [RG_LANG_EN] = "Received empty list!",
        [RG_LANG_ZH] = "收到空列表！"
    },
    {
        [RG_LANG_EN] = "Gamma Boost",
        [RG_LANG_ZH] = "伽马增强"
    },
    {
        [RG_LANG_EN] = "Day",
        [RG_LANG_ZH] = "日"
    },
    {
        [RG_LANG_EN] = "Hour",
        [RG_LANG_ZH] = "时"
    },
    {
        [RG_LANG_EN] = "Min",
        [RG_LANG_ZH] = "分"
    },
    {
        [RG_LANG_EN] = "Sec",
        [RG_LANG_ZH] = "秒"
    },
    {
        [RG_LANG_EN] = "Sync",
        [RG_LANG_ZH] = "同步"
    },
    {
        [RG_LANG_EN] = "RTC config",
        [RG_LANG_ZH] = "RTC设置"
    },
    {
        [RG_LANG_EN] = "Palette",
        [RG_LANG_ZH] = "调色板"
    },
    {
        [RG_LANG_EN] = "RTC config",
        [RG_LANG_ZH] = "RTC设置"
    },
    {
        [RG_LANG_EN] = "SRAM autosave",
        [RG_LANG_ZH] = "SRAM自动保存"
    },
    {
        [RG_LANG_EN] = "Enable BIOS",
        [RG_LANG_ZH] = "启用BIOS"
    },
    {
        [RG_LANG_EN] = "Name",
        [RG_LANG_ZH] = "名称"
    },
    {
        [RG_LANG_EN] = "Artist",
        [RG_LANG_ZH] = "艺术家"
    },
    {
        [RG_LANG_EN] = "Copyright",
        [RG_LANG_ZH] = "版权"
    },
    {
        [RG_LANG_EN] = "Playing",
        [RG_LANG_ZH] = "播放中"
    },
    {
        [RG_LANG_EN] = "Palette",
        [RG_LANG_ZH] = "调色板"
    },
    {
        [RG_LANG_EN] = "Overscan",
        [RG_LANG_ZH] = "过扫描"
    },
    {
        [RG_LANG_EN] = "Crop sides",
        [RG_LANG_ZH] = "裁剪两侧"
    },
    {
        [RG_LANG_EN] = "Sprite limit",
        [RG_LANG_ZH] = "精灵限制"
    },
    {
        [RG_LANG_EN] = "Overscan",
        [RG_LANG_ZH] = "过扫描"
    },
    {
        [RG_LANG_EN] = "Palette",
        [RG_LANG_ZH] = "调色板"
    },
    {
        [RG_LANG_EN] = "Profile",
        [RG_LANG_ZH] = "配置"
    },
    {
        [RG_LANG_EN] = "<profile name>",
        [RG_LANG_ZH] = "<配置名称>"
    },
    {
        [RG_LANG_EN] = "Controls",
        [RG_LANG_ZH] = "控制"
    },
    {
        [RG_LANG_EN] = "Audio enable",
        [RG_LANG_ZH] = "启用音频"
    },
    {
        [RG_LANG_EN] = "Audio filter",
        [RG_LANG_ZH] = "音频过滤",
    },


    // rg_gui.c
    {
        [RG_LANG_EN] = "Folder is empty.",
        [RG_LANG_ZH] = "文件夹为空。"
    },
    {
        [RG_LANG_EN] = "No",
        [RG_LANG_ZH] = "否"
    },
    {
        [RG_LANG_EN] = "OK",
        [RG_LANG_ZH] = "确定"
    },
    {
        [RG_LANG_EN] = "On",
        [RG_LANG_ZH] = "开"
    },
    {
        [RG_LANG_EN] = "Off",
        [RG_LANG_ZH] = "关"
    },
    {
        [RG_LANG_EN] = "Horiz",
        [RG_LANG_ZH] = "水平"
    },
    {
        [RG_LANG_EN] = "Vert",
        [RG_LANG_ZH] = "垂直"
    },
    {
        [RG_LANG_EN] = "Both",
        [RG_LANG_ZH] = "两者"
    },
    {
        [RG_LANG_EN] = "Fit",
        [RG_LANG_ZH] = "适应"
    },
    {
        [RG_LANG_EN] = "Full ",
        [RG_LANG_ZH] = "全屏 "
    },
    {
        [RG_LANG_EN] = "Zoom",
        [RG_LANG_ZH] = "缩放"
    },

    // Led options
    {
        [RG_LANG_EN] = "LED options",
        [RG_LANG_ZH] = "LED选项"
    },
    {
        [RG_LANG_EN] = "System activity",
        [RG_LANG_ZH] = "系统活动"
    },
    {
        [RG_LANG_EN] = "Disk activity",
        [RG_LANG_ZH] = "磁盘活动"
    },
    {
        [RG_LANG_EN] = "Low battery",
        [RG_LANG_ZH] = "电量低"
    },
    {
        [RG_LANG_EN] = "Default",
        [RG_LANG_ZH] = "默认"
    },
    {
        [RG_LANG_EN] = "<None>",
        [RG_LANG_ZH] = "<无>"
    },

    // Wifi
    {
        [RG_LANG_EN] = "Not connected",
        [RG_LANG_ZH] = "未连接"
    },
    {
        [RG_LANG_EN] = "Connecting...",
        [RG_LANG_ZH] = "连接中..."
    },
    {
        [RG_LANG_EN] = "Disconnecting...",
        [RG_LANG_ZH] = "断开中..."
    },
    {
        [RG_LANG_EN] = "(empty)",
        [RG_LANG_ZH] = "(空)"
    },
    {
        [RG_LANG_EN] = "Wi-Fi AP",
        [RG_LANG_ZH] = "Wi-Fi热点"
    },
    {
        [RG_LANG_EN] = "Start access point?\n\nSSID: retro-go\nPassword: retro-go\n\nBrowse: http://192.168.4.1/",
        [RG_LANG_ZH] = "启动热点？\n\nSSID: retro-go\n密码: retro-go\n\n访问: http://192.168.4.1/"
    },
    {
        [RG_LANG_EN] = "Wi-Fi enable",
        [RG_LANG_ZH] = "启用Wi-Fi"
    },
    {
        [RG_LANG_EN] = "Wi-Fi access point",
        [RG_LANG_ZH] = "Wi-Fi热点"
    },
    {
        [RG_LANG_EN] = "Network",
        [RG_LANG_ZH] = "网络"
    },
    {
        [RG_LANG_EN] = "IP address",
        [RG_LANG_ZH] = "IP地址"
    },

    // retro-go settings
    {
        [RG_LANG_EN] = "Brightness",
        [RG_LANG_ZH] = "亮度"
    },
    {
        [RG_LANG_EN] = "Volume",
        [RG_LANG_ZH] = "音量"
    },
    {
        [RG_LANG_EN] = "Audio out",
        [RG_LANG_ZH] = "音频输出"
    },
    {
        [RG_LANG_EN] = "Font type",
        [RG_LANG_ZH] = "字体"
    },
    {
        [RG_LANG_EN] = "Theme",
        [RG_LANG_ZH] = "主题"
    },
    {
        [RG_LANG_EN] = "Show clock",
        [RG_LANG_ZH] = "显示时钟"
    },
    {
        [RG_LANG_EN] = "Timezone",
        [RG_LANG_ZH] = "时区"
    },
    {
        [RG_LANG_EN] = "Wi-Fi options",
        [RG_LANG_ZH] = "Wi-Fi选项"
    },

    // app settings
    {
        [RG_LANG_EN] = "Scaling",
        [RG_LANG_ZH] = "缩放"
    },
    {
        [RG_LANG_EN] = "Factor",
        [RG_LANG_ZH] = "倍率"
    },
    {
        [RG_LANG_EN] = "Filter",
        [RG_LANG_ZH] = "滤镜"
    },
    {
        [RG_LANG_EN] = "Border",
        [RG_LANG_ZH] = "边框"
    },
    {
        [RG_LANG_EN] = "Speed",
        [RG_LANG_ZH] = "速度"
    },

    // about menu
    {
        [RG_LANG_EN] = "Version",
        [RG_LANG_ZH] = "版本"
    },
    {
        [RG_LANG_EN] = "Date",
        [RG_LANG_ZH] = "日期"
    },
    {
        [RG_LANG_EN] = "Target",
        [RG_LANG_ZH] = "目标"
    },
    {
        [RG_LANG_EN] = "Website",
        [RG_LANG_ZH] = "网站"
    },
    {
        [RG_LANG_EN] = "Options",
        [RG_LANG_ZH] = "选项"
    },
    {
        [RG_LANG_EN] = "View credits",
        [RG_LANG_ZH] = "查看致谢",
    },
    {
        [RG_LANG_EN] = "Debug menu",
        [RG_LANG_ZH] = "调试菜单"
    },
    {
        [RG_LANG_EN] = "Reset settings",
        [RG_LANG_ZH] = "重置设置"
    },

    // save slot
    {
        [RG_LANG_EN] = "Slot 0",
        [RG_LANG_ZH] = "槽位0"
    },
    {
        [RG_LANG_EN] = "Slot 1",
        [RG_LANG_ZH] = "槽位1"
    },
    {
        [RG_LANG_EN] = "Slot 2",
        [RG_LANG_ZH] = "槽位2"

    },
    {
        [RG_LANG_EN] = "Slot 3",
        [RG_LANG_ZH] = "槽位3"
    },

    // game menu
    {
        [RG_LANG_EN] = "Save & Continue",
        [RG_LANG_ZH] = "保存并继续"
    },
    {
        [RG_LANG_EN] = "Save & Quit",
        [RG_LANG_ZH] = "保存并退出"
    },
    {
        [RG_LANG_EN] = "Load game",
        [RG_LANG_ZH] = "载入游戏"
    },
    {
        [RG_LANG_EN] = "Reset",
        [RG_LANG_ZH] = "重置"
    },
    {
        [RG_LANG_EN] = "Netplay",
        [RG_LANG_ZH] = "网络对战"
    },
    {
        [RG_LANG_EN] = "About",
        [RG_LANG_ZH] = "关于"
    },
    {
        [RG_LANG_EN] = "Quit",
        [RG_LANG_ZH] = "退出"
    },
    {
        [RG_LANG_EN] = "Soft reset",
        [RG_LANG_ZH] = "软重置"
    },
    {
        [RG_LANG_EN] = "Hard reset",
        [RG_LANG_ZH] = "硬重置"
    },

    {
        [RG_LANG_EN] = "Reset Emulation?",
        [RG_LANG_ZH] = "重置模拟？"
    },
    {
        [RG_LANG_EN] = "Save",
        [RG_LANG_ZH] = "保存"
    },
    {
        [RG_LANG_EN] = "Load",
        [RG_LANG_ZH] = "载入"
    },
    // end of rg_gui.c


    // main.c
    {
        [RG_LANG_EN] = "Show",
        [RG_LANG_ZH] = "显示"
    },
    {
        [RG_LANG_EN] = "Hide",
        [RG_LANG_ZH] = "隐藏"
    },
    {
        [RG_LANG_EN] = "Tabs Visibility",
        [RG_LANG_ZH] = "标签可见性"
    },

    // scroll modes
    {
        [RG_LANG_EN] = "Center",
        [RG_LANG_ZH] = "居中"
    },
    {
        [RG_LANG_EN] = "Paging",
        [RG_LANG_ZH] = "翻页"
    },

    // start screen
    {
        [RG_LANG_EN] = "Auto",
        [RG_LANG_ZH] = "自动"
    },
    {
        [RG_LANG_EN] = "Carousel",
        [RG_LANG_ZH] = "轮播"
    },
    {
        [RG_LANG_EN] = "Browser",
        [RG_LANG_ZH] = "浏览"
    },

    // preview
    {
        [RG_LANG_EN] = "None",
        [RG_LANG_ZH] = "无"
    },
    {
        [RG_LANG_EN] = "Cover,Save",
        [RG_LANG_ZH] = "封面,存档"
    },
    {
        [RG_LANG_EN] = "Save,Cover",
        [RG_LANG_ZH] = "存档,封面"
    },
    {
        [RG_LANG_EN] = "Cover only",
        [RG_LANG_ZH] = "仅封面"
    },
    {
        [RG_LANG_EN] = "Save only",
        [RG_LANG_ZH] = "仅存档"
    },

    // startup app
    {
        [RG_LANG_EN] = "Last game",
        [RG_LANG_ZH] = "上次游戏"
    },
    {
        [RG_LANG_EN] = "Launcher",
        [RG_LANG_ZH] = "启动器"
    },

    // launcher options
    {
        [RG_LANG_EN] = "Launcher Options",
        [RG_LANG_ZH] = "启动器选项"
    },
    {
        [RG_LANG_EN] = "Color theme",
        [RG_LANG_ZH] = "颜色主题"
    },
    {
        [RG_LANG_EN] = "Preview",
        [RG_LANG_ZH] = "预览"
    },
    {
        [RG_LANG_EN] = "Scroll mode",
        [RG_LANG_ZH] = "滚动模式"
    },
    {
        [RG_LANG_EN] = "Start screen",
        [RG_LANG_ZH] = "启动画面"
    },
    {
        [RG_LANG_EN] = "Hide tabs",
        [RG_LANG_ZH] = "隐藏标签"
    },
    {
        [RG_LANG_EN] = "File server",
        [RG_LANG_ZH] = "文件服务器"
    },
    {
        [RG_LANG_EN] = "Startup app",
        [RG_LANG_ZH] = "启动应用"
    },
    {
        [RG_LANG_EN] = "Build CRC cache",
        [RG_LANG_ZH] = "构建CRC缓存"
    },
    {
        [RG_LANG_EN] = "Check for updates",
        [RG_LANG_ZH] = "检查更新"
    },
    {
        [RG_LANG_EN] = "HTTP Server Busy...",
        [RG_LANG_ZH] = "HTTP服务器忙..."
    },
    {
        [RG_LANG_EN] = "SD Card Error",
        [RG_LANG_ZH] = "SD卡错误"
    },
    {
        [RG_LANG_EN] = "Storage mount failed.\nMake sure the card is FAT32.",
        [RG_LANG_ZH] = "存储挂载失败。\n请确保SD卡为FAT32格式。"
    },
    // end of main.c


    // applications.c
    {
        [RG_LANG_EN] = "Scanning %s %d/%d",
        [RG_LANG_ZH] = "扫描 %s %d/%d"
    },
    // message when no rom
    {
        [RG_LANG_EN] = "Welcome to Retro-Go!",
        [RG_LANG_ZH] = "欢迎使用Retro-Go！"
    },
    {
        [RG_LANG_EN] = "Place roms in folder: %s",
        [RG_LANG_ZH] = "将ROM放入文件夹：%s"
    },
    {
        [RG_LANG_EN] = "With file extension: %s",
        [RG_LANG_ZH] = "文件扩展名：%s"
    },
    {
        [RG_LANG_EN] = "You can hide this tab in the menu",
        [RG_LANG_ZH] = "你可以在菜单中隐藏此标签"
    },
    {
        [RG_LANG_EN] = "You have no %s games",
        [RG_LANG_ZH] = "你没有%s游戏"
    },
    {
        [RG_LANG_EN] = "File not found",
        [RG_LANG_ZH] = "文件未找到"
    },

    // rom options
    {
        [RG_LANG_EN] = "Name",
        [RG_LANG_ZH] = "名称"
    },
    {
        [RG_LANG_EN] = "Folder",
        [RG_LANG_ZH] = "文件夹"
    },
    {
        [RG_LANG_EN] = "Size",
        [RG_LANG_ZH] = "大小"
    },
    {
        [RG_LANG_EN] = "CRC32",
        [RG_LANG_ZH] = "CRC32"
    },
    {
        [RG_LANG_EN] = "Delete file",
        [RG_LANG_ZH] = "删除文件"
    },
    {
        [RG_LANG_EN] = "Close",
        [RG_LANG_ZH] = "关闭"
    },
    {
        [RG_LANG_EN] = "File properties",
        [RG_LANG_ZH] = "文件属性"
    },
    {
        [RG_LANG_EN] = "Delete selected file?",
        [RG_LANG_ZH] = "删除所选文件？"
    },


    // in-game menu
    {
        [RG_LANG_EN] = "Resume game",
        [RG_LANG_ZH] = "继续游戏"
    },
    {
        [RG_LANG_EN] = "New game",
        [RG_LANG_ZH] = "新游戏"
    },
    {
        [RG_LANG_EN] = "Del favorite",
        [RG_LANG_ZH] = "删除收藏"
    },
    {
        [RG_LANG_EN] = "Add favorite",
        [RG_LANG_ZH] = "添加收藏"
    },
    {
        [RG_LANG_EN] = "Delete save",
        [RG_LANG_ZH] = "删除存档"
    },
    {
        [RG_LANG_EN] = "Properties",
        [RG_LANG_ZH] = "属性"
    },
    {
        [RG_LANG_EN] = "Resume",
        [RG_LANG_ZH] = "继续"
    },
    {
        [RG_LANG_EN] = "Delete save?",
        [RG_LANG_ZH] = "删除存档？"
    },
    {
        [RG_LANG_EN] = "Delete sram file?",
        [RG_LANG_ZH] = "删除SRAM文件？"
    },
    // end of applications.c


    // rg_system.c
    {
        [RG_LANG_EN] = "App unresponsive... Hold MENU to quit!",
        [RG_LANG_ZH] = "应用无响应...按住MENU退出！"
    },
    {
        [RG_LANG_EN] = "Reset all settings",
        [RG_LANG_ZH] = "重置所有设置"
    },
    {
        [RG_LANG_EN] = "Reboot to factory ",
        [RG_LANG_ZH] = "恢复出厂设置"
    },
    {
        [RG_LANG_EN] = "Reboot to launcher",
        [RG_LANG_ZH] = "重启到启动器"
    },
    {
        [RG_LANG_EN] = "Recovery mode",
        [RG_LANG_ZH] = "恢复模式"
    },
    {
        [RG_LANG_EN] = "System Panic!",
        [RG_LANG_ZH] = "系统错误！"
    },
    {
        [RG_LANG_EN] = "Save failed",
        [RG_LANG_ZH] = "保存失败"
    },
    // end of rg_system.c
};
