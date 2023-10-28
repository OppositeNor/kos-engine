#include "kos_engine/input_handler.h"
void KEInputHandler::SetInputStatePressed(int p_key)
{
    auto key = input_map.find(p_key);
    if (key == input_map.end())
        return;
    auto key_list = key->second;
    for (auto iter = key_list.begin(); iter != key_list.end(); ++iter)
    {
        input_state_map[*iter] = InputState::JustPressed;
    }
}

void KEInputHandler::SetInputStateReleased(int p_key)
{
    auto key = input_map.find(p_key);
    if (key == input_map.end())
        return;
    auto key_list = key->second;
    for (auto iter = key_list.begin(); iter != key_list.end(); ++iter)
    {
        input_state_map[*iter] = InputState::JustReleased;
    }
}

KEInputHandler::InputState KEInputHandler::GetInputState(const KEString& p_key) const
{
    return input_state_map.at(p_key);
}

void KEInputHandler::AddInput(const KEString& input_name, int p_key)
{
    input_map[p_key].push_back(input_name);
    input_state_map[input_name] = InputState::Released;
}

void KEInputHandler::ClearInput()
{
    input_map.clear();
    input_state_map.clear();
}

void KEInputHandler::UpdateInput()
{
    for (auto iter = input_state_map.begin(); iter != input_state_map.end(); ++iter)
    {
        if (iter->second == InputState::JustPressed)
            iter->second = InputState::Pressed;
        else if (iter->second == InputState::JustReleased)
            iter->second = InputState::Released;
    }
}

bool KEInputHandler::IsInputPressed(const KEString& p_key) const
{
    return input_state_map.at(p_key) & InputState::Pressed;
}

bool KEInputHandler::IsInputReleased(const KEString& p_key) const
{
    return input_state_map.at(p_key) & InputState::Released;
}

bool KEInputHandler::IsInputJustPressed(const KEString& p_key) const
{
    return input_state_map.at(p_key) == InputState::JustPressed;
}

bool KEInputHandler::IsInputJustReleased(const KEString& p_key) const
{
    return input_state_map.at(p_key) == InputState::JustReleased;
}

void KEInputHandler::KeyFunc(int p_key, int p_action)
{
    switch (p_action)
    {
    case CG_RELEASE:
        SetInputStateReleased(p_key);
        break;
    case CG_PRESS:
        SetInputStatePressed(p_key);
        break;
    default:
        break;
    }
}