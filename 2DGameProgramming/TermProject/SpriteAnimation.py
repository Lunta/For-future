from SpriteImage import*


class SpriteAnimation:
    def __init__(self):
        self._m_SpriteState_List = []
        self._m_SpriteImage_List = []

        self._m_StateState = POINT()
        self._m_StateState.execute = 0
        self._m_StateState.action = 1
        self._m_StateState.exit = 2

        self._m_MaxState = []
        self._m_StateDelay = []
        self._m_StateExecute = []
        self._m_StateAction = []
        self._m_StateExit = []

        self._m_CurrentState = None
        self._m_NextState = None
        self._m_DelayCount = 0

    def set_sprite(self, path, state_name, w=1, h=1):
        self._m_SpriteState_List.append(state_name)
        self._m_SpriteImage_List.append(SpriteImage(path, w, h))
        self._m_MaxState.append(0)
        self._m_StateDelay.append([0 for st in range(3)])
        self._m_StateExecute.append([0 for st in range(2)])
        self._m_StateAction.append([0 for st in range(2)])
        self._m_StateExit.append([0 for st in range(2)])

    def set_state(self, state_index, val, execute_start, execute_end, exit_start, exit_end):
        self._m_MaxState[self._m_SpriteState_List.index(state_index)] = val
        self._m_StateExecute[self._m_SpriteState_List.index(state_index)][0] = execute_start
        self._m_StateExecute[self._m_SpriteState_List.index(state_index)][1] = execute_end
        self._m_StateAction[self._m_SpriteState_List.index(state_index)][0] = execute_end
        self._m_StateAction[self._m_SpriteState_List.index(state_index)][1] = exit_start
        self._m_StateExit[self._m_SpriteState_List.index(state_index)][0] = exit_start
        self._m_StateExit[self._m_SpriteState_List.index(state_index)][1] = exit_end

    def set_state_delay(self, state_index, execute_delay, action_delay, exit_delay):
        self._m_StateDelay[self._m_SpriteState_List.index(state_index)][0] = execute_delay
        self._m_StateDelay[self._m_SpriteState_List.index(state_index)][1] = action_delay
        self._m_StateDelay[self._m_SpriteState_List.index(state_index)][2] = exit_delay

    def update_state(self, state_index):
        pass
        '''
        # 현재 상태와 동일하면 생략
        if state_index == self._m_CurrentState:
            return None

        # 공격 중에는 상태 갱신 생략
        if (ESpriteState::sprite_state_attack == m_stCurrent && ESpriteState::sprite_state_guard != s && ESpriteState::sprite_state_hit != s) return
        # 피격 중에는 상태 갱신 생략
        if (ESpriteState::sprite_state_guard == m_stCurrent && ESpriteState::sprite_state_hit != s ) return
        if (ESpriteState::sprite_state_hit == m_stCurrent && ESpriteState::sprite_state_idle == s)
            m_stCurrent = s
            m_ptCurrentAnimationState.x = m_iStateExecute[m_stCurrent][0]
            m_ptCurrentAnimationState.y = m_stCurrent * 2 + (m_bLeft ? 1 : 0)
            return

        if (ESpriteState::sprite_state_hit == m_stCurrent) return;

        # 현재 상태가 idle 이 아니고
        # 현재 진행중인 상태가 진입 상태일 경우
        # 퇴장 상태로 변경하지 않고 갱신
        if (ESpriteState::sprite_state_idle != s || ESpriteState::sprite_state_hit == s)
            m_stCurrent = s;
            m_ptCurrentAnimationState.x = m_iStateExecute[m_stCurrent][0];
            m_ptCurrentAnimationState.y = m_stCurrent * 2 + (m_bLeft ? 1 : 0);

        # 퇴장 상태로 갱신
        else:
            // 이미 퇴장중이면 취소
            if (GetCurrentStateState() == StateState::state_state_exit) return;
            m_stNext = s;
            m_ptCurrentAnimationState.x = m_iStateExit[m_stCurrent][0];
        # 딜레이 카운터 초기화
        self._m_DelayCount = 0;
        '''

    def get_current_state(self):
        return self._m_CurrentState

    def get_current_state_state(self):
        pass
        '''
        # 진입 상태로 초기화
        State_state = state_state_execute
        # 진행 상태보다 많이 진행하고 있는 경우
        if (m_ptCurrentAnimationState.x >= m_iStateAction[m_stCurrent][1]) State_state = state_state_exit
        # 진행상태일 경우
        else if (m_ptCurrentAnimationState.x >= m_iStateAction[m_stCurrent][0]) State_state = state_state_action
        return State_state
        '''
    def update(self, reset=False):
        pass
        '''
        if reset:
            self._m_CurrentState = ESpriteState::sprite_state_pop;
            self._m_ptCurrentAnimationState.x = m_iStateExecute[m_stCurrent][0];
            self._m_ptCurrentAnimationState.y = (ESpriteState::sprite_state_pop * 2) + (m_bLeft ? 1 : 0);
            return None

        # execute - action - exit
        State_state = self.get_current_state_state()

        # 딜레이 카운터 갱신
        (++m_nCount) %= (m_iStateDelay[m_stCurrent][State_state]);

        # 딜레이 카운터로 갱신 여부 확인
        if self._m_DelayCount is not 0:
            return None

        # 이미지 갱신
        (++m_ptCurrentAnimationState.x) %= m_iStateExit[m_stCurrent][1];
        #초기화는
        if self._m_ptCurrentAnimationState.x is 0:
            # 다음 상태로 변경
            m_stCurrent = m_stNext;
            m_ptCurrentAnimationState.x = m_iStateExecute[m_stCurrent][0]
            m_ptCurrentAnimationState.y = m_stCurrent * 2 + (m_bLeft ? 1 : 0)
        '''

