#pragma once
#include "sdk.h"
#include <stdio.h>

#define PI 3.141592653589793f

namespace APEX
{
    Vector CalcAngle(Vector viewAngle, Vector aimPos)
    {
        Vector angle = {0, 0, 0};

        Vector delta = aimPos - viewAngle;

        angle.x = -asin(delta.z / delta.Size()) * (180.0f / PI); // pitch
        angle.y = atan2(delta.y, delta.x) * (180.0f / PI);       // yaw

        return angle;
    }

    Vector NormalizeAngles(Vector angle)
    {
        while (angle.x > 89.0f)
            angle.x -= 180.f;

        while (angle.x < -89.0f)
            angle.x += 180.f;

        while (angle.y > 180.f)
            angle.y -= 360.f;

        while (angle.y < -180.f)
            angle.y += 360.f;

        return angle;
    }

    float GetFov(Vector viewAngle, Vector aimAngle)
    {
        Vector delta = aimAngle - viewAngle;
        delta        = NormalizeAngles(delta);
        return sqrt(pow(delta.x, 2.0f) + pow(delta.y, 2.0f));
    }

    void Aimbot()
    {
        // 自瞄
        if (GetAsyncKeyState(VK_RBUTTON) && *localPlayer != NULL)
        {
            Vector        aimbotAngle  = {0, 0, 0};
            ClientEntity *aimbotEntity = NULL;

            for (size_t i = 0; i < NUM_ENT_ENTRIES; i++)
            {
                ClientEntityInfo *entityInfo = &clientEntityList->clientEntityInfo[i];

                if (ClientEntity *entity = entityInfo->m_pEntity)
                {
                    if (entity != *localPlayer &&
                        entity->m_iTeamNum != (*localPlayer)->m_iTeamNum &&
                        entity->m_iHealth > 0)
                    {
                        // 遍历骨骼
                        for (int j = 3; j <= 6; j += 3)
                        {
                            // 瞄准位置
                            Matrix3x4 boneMatrix = entity->m_BoneMatrix[j + 4];
                            Vector    vecBone    = Vector{boneMatrix.m14, boneMatrix.m24, boneMatrix.m34} + entity->m_vecOrigin;

                            Vector aimbotAngleTemp = CalcAngle((*localPlayer)->m_cameraOrigin, vecBone);

                            // 冒泡排序
                            if (GetFov((*localPlayer)->m_ViewAngles, aimbotAngleTemp) < GetFov((*localPlayer)->m_ViewAngles, aimbotAngle) || aimbotEntity == NULL)
                            {
                                aimbotEntity = entity;
                                aimbotAngle  = aimbotAngleTemp;
                            }
                        }
                    }
                }
            }

            // Set ViewAngles
            if (aimbotEntity != NULL &&
                GetFov((*localPlayer)->m_ViewAngles, aimbotAngle) < 20 &&
                ((*localPlayer)->m_vecOrigin - aimbotEntity->m_vecOrigin).Size() < 5000)
            {
                Vector delta = NormalizeAngles(aimbotAngle - (*localPlayer)->m_ViewAngles);
                (*localPlayer)->m_ViewAngles.x += delta.x / 10; // pitch
                (*localPlayer)->m_ViewAngles.y += delta.y / 10; // yaw
            }
        }
    }

    void Glow()
    {
        if (*localPlayer != NULL)
        {
            for (size_t i = 0; i < NUM_ENT_ENTRIES; i++)
            {
                ClientEntityInfo *entityInfo = &clientEntityList->clientEntityInfo[i];

                if (ClientEntity *entity = entityInfo->m_pEntity)
                {
                    // 开启发光
                    if ((*localPlayer)->m_iTeamNum == entity->m_iTeamNum)
                    {
                        entity->GLOW_ENABLE        = 1;
                        entity->GLOW_THROUGH_WALLS = 2;
                        entity->m_GlowColor.y      = 30;
                    }
                    else
                    {
                        entity->GLOW_ENABLE        = 1;
                        entity->GLOW_THROUGH_WALLS = 2;
                        entity->m_GlowColor.x      = 30;
                    }
                }
            }
        }
    }
} // namespace APEX
