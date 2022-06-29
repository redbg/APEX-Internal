#pragma once

#include "offsets.h"
#include "src/SS/Math/Math.h"
#include <Windows.h>

using namespace SS::Math;

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b)      STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size)       STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) \
    struct                                  \
    {                                       \
        unsigned char MAKE_PAD(offset);     \
        type          name;                 \
    }

#define NUM_ENT_ENTRIES 64

namespace APEX
{
    // ================================================== ClientEntity ==================================================

    struct ClientEntity
    {
        union
        {
            DEFINE_MEMBER_N(int, m_iHealth, OFFSET_HEALTH);                      // 血量
            DEFINE_MEMBER_N(Vector, m_vecOrigin, OFFSET_ORIGIN);                 // 坐标
            DEFINE_MEMBER_N(Vector, m_cameraOrigin, OFFSET_CAMERAPOS);           // 相机坐标
            DEFINE_MEMBER_N(Matrix3x4 *, m_BoneMatrix, OFFSET_BONES);            // 骨骼矩阵
            DEFINE_MEMBER_N(int, m_iTeamNum, OFFSET_TEAM);                       // 队伍
            DEFINE_MEMBER_N(Vector, m_ViewAngles, OFFSET_VIEWANGLES);            // 视角
            DEFINE_MEMBER_N(int, GLOW_ENABLE, OFFSET_GLOW_ENABLE);               // 发光
            DEFINE_MEMBER_N(int, GLOW_THROUGH_WALLS, OFFSET_GLOW_THROUGH_WALLS); // 穿墙
            DEFINE_MEMBER_N(Vector, m_GlowColor, OFFSET_GLOW_COLOR);             // 颜色
        };
    };

    struct ClientEntityInfo
    {
    public:
        ClientEntity     *m_pEntity;
        int               m_SerialNumber;
        ClientEntityInfo *m_pPrev;
        ClientEntityInfo *m_pNext;
    };

    class ClientEntityList
    {
    public:
        ClientEntityInfo clientEntityInfo[NUM_ENT_ENTRIES];
    };

    // ================================================== Data ==================================================

    DWORD64           r5apex           = (DWORD64)GetModuleHandle(NULL);
    ClientEntityList *clientEntityList = (ClientEntityList *)(r5apex + OFFSET_ENTITYLIST);
    ClientEntity    **localPlayer      = (ClientEntity **)(r5apex + OFFSET_LOCAL_ENT);
} // namespace APEX
