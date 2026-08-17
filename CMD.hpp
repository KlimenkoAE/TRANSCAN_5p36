#pragma once

#include <cstdint>
#include <utility>
#include <functional>
#include "fifo_ring.hpp"
#include "wrappers_headers.hpp"
#include <cstdio>
template<
    uint8_t MAX_CMD_LEN,
    uint8_t MAX_CMD_ARGS,
    uint8_t MAX_CMD_CNT,
    uint8_t CMD_SEPARATOR
>
class CommandSeparator
{
    enum class CMD_State : uint8_t
    {
        NONE,
        C,
        CM,
        COMMAND
    };

    using Handler =
        std::function<void(const uint8_t* args, uint8_t args_cnt)>;

    struct CmdEntry
    {
        const char* name;
        Handler handler;
    };

    inline static CmdEntry cmd_handlers[MAX_CMD_CNT];
    inline static uint8_t cmd_cnt = 0;

    inline static CMD_State cmd_state = CMD_State::NONE;

    inline static uint8_t cmd_buf[MAX_CMD_LEN];
    inline static uint8_t cmd_len = 0;

    static int FindCommand(const uint8_t* cmd)
    {
        for (uint8_t i = 0; i < cmd_cnt; ++i)
        {
            if (streq(cmd, cmd_handlers[i].name))
                return i;
        }

        return -1;
    }

    static void ExecuteCommand()
    {
        cmd_buf[cmd_len] = '\0';
        const uint8_t* command = cmd_buf + 3;
///////////////
                       for (unsigned i = 0; i < cmd_len; ++i)
    std::printf("%c", (unsigned)command[i]);
std::printf("\r\n");

///////////////


        const int index = FindCommand(command);

        if (index < 0)
            return;

        cmd_handlers[index].handler(
            nullptr,
            0
        );
    }

public:

    template<size_t N>
    static bool CmdHandlerRegister(
        const char (&name)[N],
        Handler handler)
    {
        if (cmd_cnt >= MAX_CMD_CNT)
            return false;

        cmd_handlers[cmd_cnt++] = {
            name,
            std::move(handler)
        };

        return true;
    }

    static void CMD_Filter(
        auto& FR_RX,
        uint8_t* rx_buf,
        uint32_t len)
    {
        for (uint32_t i = 0; i < len; ++i)
        {
            const uint8_t b = rx_buf[i];

            switch (cmd_state)
            {
                case CMD_State::NONE:

                    if (b == 'C')
                    {
                        cmd_state = CMD_State::C;
                    }
                    else
                    {
                        FR_RX.add_byte(b);
                    }

                    break;


                case CMD_State::C:

                    if (b == 'M')
                    {
                        cmd_state = CMD_State::CM;
                    }
                    else
                    {
                        // C оказался обычным байтом.
                        FR_RX.add_byte('C');

                        if (b == 'C')
                        {
                            cmd_state = CMD_State::C;
                        }
                        else
                        {
                            FR_RX.add_byte(b);
                            cmd_state = CMD_State::NONE;
                        }
                    }

                    break;


                case CMD_State::CM:

                    if (b == 'D')
                    {
                        cmd_buf[0] = 'C';
                        cmd_buf[1] = 'M';
                        cmd_buf[2] = 'D';
                        cmd_len = 3;
                        cmd_state = CMD_State::COMMAND;
                    }
                    else
                    {
                        // CM оказалось обычными данными.
                        FR_RX.add_byte('C');
                        FR_RX.add_byte('M');

                        if (b == 'C')
                        {
                            cmd_state = CMD_State::C;
                        }
                        else
                        {
                            FR_RX.add_byte(b);
                            cmd_state = CMD_State::NONE;
                        }
                    }

                    break;


                case CMD_State::COMMAND:

                    if (b == CMD_SEPARATOR)
                    {
                        cmd_buf[cmd_len] = '\0';


                        ExecuteCommand();

                        cmd_len = 0;
                        cmd_state = CMD_State::NONE;
                    }
                    else
                    {
                        if (cmd_len < MAX_CMD_LEN - 1)
                        {
                            cmd_buf[cmd_len++] = b;
                        }
                        else
                        {
                            // Команда слишком длинная.
                            //возвращаем все потоку
                             for (uint8_t j = 0; j < cmd_len; ++j)
                                FR_RX.add_byte(cmd_buf[j]);
                            if(b=='C'){
                            cmd_len = 1;
                            cmd_state = CMD_State::C;
                            } else{   
                            cmd_len = 0;
                            cmd_state = CMD_State::NONE;
                            }
                        }
                    }

                    break;
            }
        }
    }
};