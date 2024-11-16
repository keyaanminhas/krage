// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>
#include <Windows.h>
#include "sdk.h"
#include <vector>
#include <sstream>
#include <math.h>

# define M_PI 3.14159265358979323846f


cl_enginefunc_t* pEnginefuncs = NULL;
cl_enginefunc_t gEngfuncs;




//r_studio_interface_t** ppinterface;

//engine_studio_api_t* pstudio;
//engine_studio_api_t gstudio;

float set_angle_y = 0;
float set_angle_x = 0;


float* punch_angle_y;
float* punch_angle_x;
float old_punch_y;

float* view_x_ptr;

std::vector<float> distances(10000, 50);
short int current_enemy = 0;




struct player_loc {
    float distance = 10000;
    float x = 0;
    float y = 0;
    float z = 0;
};


float calc_distance(const float& x, const float& y, const float& z) {
    return sqrtf(x * x + y * y + z * z);

}


static float aimatx(const player_loc enemy_pos) {
    float side_angle = atan2f(enemy_pos.y, enemy_pos.x);
    side_angle = side_angle * (180.0f / M_PI);
    return side_angle;
    //gEngfuncs.SetViewAngles(&(up_angle));
}


static float aimaty(const player_loc enemy_pos) {
    float up_angle = atan2f(enemy_pos.z, sqrtf(enemy_pos.y * enemy_pos.y + enemy_pos.x * enemy_pos.x));
    up_angle = up_angle * (180.0f / M_PI);
    up_angle = up_angle * -1;

    /*
    std::cout << up_angle << "          " << *punch_angle_y;
    if (punch_angle_y != 0) {
        up_angle = up_angle - old_punch_y - (4 * (*punch_angle_y));
        old_punch_y = (4 * (*punch_angle_y));
    }
    else {
        old_punch_y = 0.00f;
    }
    */
    return up_angle;
    //gEngfuncs.SetViewAngles(&(up_angle));
}
void No_Flash() {
    screenfade_s fade;
    gEngfuncs.pfnGetScreenFade(&fade);

    //        std::cout << "DATA: rgba" << " " << fade.fader << " " << fade.fadeg << " " << fade.fadeb << " " << fade.fadealpha;
    // std::cout << int(fade.fader) << " " << int(fade.fadeg) << " " << int(fade.fadeb) << "\n";

    if (int(fade.fadealpha) > 0) {
        fade.fadealpha = byte(int(0));
        gEngfuncs.pfnSetScreenFade(&fade);
    }
}




void Aimbot() {
    int Max_Players = gEngfuncs.GetMaxClients();

    short int new_enemy = 0;
    player_loc closest;

    bool modified = false;
    cl_entity_t* local_player = gEngfuncs.GetLocalPlayer();
    float local_x = local_player->origin[0];
    float local_y = local_player->origin[1];
    float local_z = local_player->origin[2];
    float myloc[3] = { local_x, local_y, local_z };
    for (int i = 0; i != Max_Players; i++) {
        Sleep(0.2);
        cl_entity_s* entity = gEngfuncs.GetEntityByIndex(i);
        if (!(entity->player)) continue;
        //std::cout << local_player->model->name << "\n";


        float x = entity->origin[0];
        float y = entity->origin[1];
        float z = entity->origin[2];
        float opploc[3] = { x,y,z };
        pmtrace_t* traced_player = gEngfuncs.PM_TraceLine(myloc, opploc, PM_TRACELINE_PHYSENTSONLY, 0, 1);
        //if (traced_player->ent == -1) {
            //std::cout << traced_player->fraction;
            //std::cout << "    " << traced_player->ent << "    " << traced_player->hitgroup << "\n";


            float current_distance = calc_distance(x - local_x, y - local_y, z - local_z);
            if ((x != 0) && (y != 0) && (z != 0) && (current_distance != 0)) {
                //std::cout << current_distance << "\n";
                try
                {
                    //model_s* enemy_info = entity->model;
                    entity_state_t state = entity->curstate;


                    //std::cout << state.solid << "\n";
                    if (state.solid != 3) {
                        current_distance = 10000;
                        Sleep(0.2);
                    }
                }
                catch (...)
                {
                    current_distance = 10000;
                }
                distances[i] = current_distance;
                // TERRORIST MODELS = Guerilla artic elite phenoix
                // models/player/terror/terror.mdl 
                if (current_distance!= 10000 and current_distance <= closest.distance) {
                    std::cout << closest.distance << "    " << current_distance << "\n";
                    modified = true;
                    closest.distance = current_distance;
                    closest.x = x - local_x;
                    closest.y = y - local_y;
                    closest.z = z - local_z;
                    new_enemy = i;
                }
            }
        }
    //}


    if (new_enemy != current_enemy) {
        Sleep(40);

        current_enemy = new_enemy;
    }
    if (closest.distance != 10000) {
        set_angle_y = aimaty(closest);
        set_angle_x = aimatx(closest);
    }

    float current_angles;
    gEngfuncs.GetViewAngles(&current_angles);
    current_angles = set_angle_y;
    if (modified == true) {
        gEngfuncs.SetViewAngles(&current_angles);
    }
    if (set_angle_x < 0) {
        set_angle_x = 360 + set_angle_x;
    }
    if (modified == true) {
        *view_x_ptr = set_angle_x;
    }
}

DWORD WINAPI HackThread(LPVOID param) {
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);




    //MessageBox(NULL, L"SUCCESSFULLY INJECTED!", L"INJECTION", MB_OK);
    MessageBox(NULL, L"WELCOME TO KRAGE HACKS!", L"INJECTION", MB_OK);

    std::cout << "KRAGE HACKS BY KEYAAN\n";


    uintptr_t pHWDLL = (uintptr_t)GetModuleHandle(L"hw.dll");


    if (!pHWDLL) {
    
        std::cout << "hw.dll not found! \n";

    }

    pEnginefuncs = (cl_enginefunc_t*)(pHWDLL + 0x00166A98);


    memcpy(&gEngfuncs, pEnginefuncs, sizeof(cl_enginefunc_t));

    gEngfuncs.Con_Printf((char*)"KRAGE Hack loaded\n");



//    pstudio = (engine_studio_api_t*)(pHWDLL + 0x00199F7);

//    memcpy(&gstudio, pstudio, sizeof(engine_studio_api_t));

//    ppinterface = (r_studio_interface_t**)(pHWDLL + 0x199FC);




    bool anti_flash = false;
    bool aim_mode = false;

    view_x_ptr = (float*)(pHWDLL + 0x10569A8);
    punch_angle_y = (float*)(pHWDLL + 0x10569B1);
    punch_angle_x = (float*)(pHWDLL + 0x10569B5);
    //typedef void(__stdcall * _getteam)();
    typedef int (*_getteam)(cl_entity_t* pEntity);
    _getteam getteam;
    getteam = (_getteam)((uintptr_t)GetModuleHandle(L"client.dll") + 0x100DF4);

    //client.dll + 0x100DF4



    while (!(GetAsyncKeyState(VK_ESCAPE) & 1)) {


        if (anti_flash) {
            No_Flash();

        }


        if (aim_mode) {
            Aimbot();
        }


        if (GetAsyncKeyState(VK_RSHIFT) & 0x8000) { anti_flash = !anti_flash;aim_mode = !aim_mode; std::cout << "[+] HACKS TOGGLED\n"; Sleep(150); };

        Sleep(1);
    }

    FreeLibraryAndExitThread((HMODULE)param, 0);
    return 0;


}



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)HackThread, NULL, 0, NULL);

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

