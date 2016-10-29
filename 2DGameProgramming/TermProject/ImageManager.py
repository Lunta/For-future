from SpriteAnimation import*


class ImageManager:
    def __init__(self):
        # Image
        self.Image_SceneBK_Logo = load_image('Resource\\Graphics\\Background\\Logo.png')
        self.Image_SceneBK_Title_Start = load_image('Resource\\Graphics\\Background\\Title_Start.png')
        self.Image_SceneBK_Title_Exit = load_image('Resource\\Graphics\\Background\\Title_Exit.png')
        self.Image_SceneBK_Play = load_image('Resource\\Graphics\\Background\\Play.png')
        self.Image_SceneBK_Gameover = load_image('Resource\\Graphics\\Background\\Gameover.png')
        self.Image_SceneBK_Ranking = load_image('Resource\\Graphics\\Background\\Logo.png')
        
        self.Image_UI_Box = load_image('Resource\\Graphics\\Background\\UI_BOX.png')

        self.Image_Meteor_Small = load_image('Resource\\Graphics\\Object\\Stone_Small.png')
        self.Image_Meteor_Big = load_image('Resource\\Graphics\\Object\\Stone_Big.png')
        self.Image_Meteor_Huge = load_image('Resource\\Graphics\\Object\\Stone_Huge.png')
        self.Image_Meteor_Boss_List = \
            [
                load_image('Resource\\Graphics\\Object\\Boss_Mercury1.png'),
                load_image('Resource\\Graphics\\Object\\Boss_Venus2.png'),
                load_image('Resource\\Graphics\\Object\\Boss_Mars3.png'),
                load_image('Resource\\Graphics\\Object\\Boss_Jupiter4.png'),
                load_image('Resource\\Graphics\\Object\\Boss_Saturn5.png'),
                load_image('Resource\\Graphics\\Object\\Boss_Uranus6.png'),
                load_image('Resource\\Graphics\\Object\\Boss_Neptune7.png'),
            ]

        # Sprite Image
        self.SpriteImage_MeteorEffect_Small = SpriteImage('Resource\\Graphics\\Sprite\\Effect\\Effect_Small.png', 'Small_Effect', 4)
        self.SpriteImage_MeteorEffect_Big = SpriteImage('Resource\\Graphics\\Sprite\\Effect\\Effect_Big.png', 'Big_Effect', 4)
        self.SpriteImage_MeteorEffect_Huge = SpriteImage('Resource\\Graphics\\Sprite\\Effect\\Effect_Huge.png', 'Huge_Effect', 4)
        self.SpriteImage_MeteorEffect_Boss = SpriteImage('Resource\\Graphics\\Sprite\\Effect\\Effect_Boss.png', 'Boss_Effect', 4)

        self.SpriteImage_PlayerEffect_Attack = SpriteImage('Resource\\Graphics\\Sprite\\Effect\\Effect_Attack.png', 'Attack_Effect', 6)
        self.SpriteImage_PlayerEffect_Kamehameha = SpriteImage('Resource\\Graphics\\Sprite\\Effect\\Kamehameha.png', 'Kamehameha', 3)

        # Sprite Animation
        # Player
        # Set Animation SpriteImage
        self.Animation_Player = SpriteAnimation()
        self.Animation_Player.set_sprite('Resource\\Graphics\\Sprite\\Player\\Idle_Normal.png', 'Idle_Normal', 6)
        self.Animation_Player.set_sprite('Resource\\Graphics\\Sprite\\Player\\MoveFront.png', 'MoveFront', 2)
        self.Animation_Player.set_sprite('Resource\\Graphics\\Sprite\\Player\\MoveBack.png', 'MoveBack', 2)
        self.Animation_Player.set_sprite('Resource\\Graphics\\Sprite\\Player\\Attack_Punch.png', 'Attack_Punch', 4)
        self.Animation_Player.set_sprite('Resource\\Graphics\\Sprite\\Player\\Attack_Punch_2.png', 'Attack_Punch_2', 6)
        self.Animation_Player.set_sprite('Resource\\Graphics\\Sprite\\Player\\Attack_Kick.png', 'Attack_Kick', 6)
        self.Animation_Player.set_sprite('Resource\\Graphics\\Sprite\\Player\\PowerUP.png', 'PowerUP', 6)
        # Set Animation State
        self.Animation_Player.set_state('Idle_Normal', 6, 0, 6, 6, 6)
        self.Animation_Player.set_state('MoveFront', 2, 0, 1, 2, 2)
        self.Animation_Player.set_state('MoveBack', 2, 0, 1, 2, 2)
        self.Animation_Player.set_state('Attack_Punch', 4, 0, 1, 2, 4)
        self.Animation_Player.set_state('Attack_Punch_2', 6, 0, 2, 3, 6)
        self.Animation_Player.set_state('Attack_Kick', 6, 0, 1, 2, 6)
        self.Animation_Player.set_state('PowerUP', 6, 0, 0, 0, 6)
        # Set Animation Delay
        self.Animation_Player.set_state_delay('Idle_Normal', 6, 1, 1)
        self.Animation_Player.set_state_delay('MoveFront', 5, 100, 1)
        self.Animation_Player.set_state_delay('MoveBack', 5, 100, 1)
        self.Animation_Player.set_state_delay('Attack_Punch', 3, 3, 3)
        self.Animation_Player.set_state_delay('Attack_Punch_2', 3, 3, 2)
        self.Animation_Player.set_state_delay('Attack_Kick', 3, 3, 2)
        self.Animation_Player.set_state_delay('PowerUP', 1, 1, 5)

        # Player Power Up
        # Set Animation SpriteImage
        self.Animation_Player_PowerUp = SpriteAnimation()
        self.Animation_Player_PowerUp.set_sprite('Resource\\Graphics\\Sprite\\Player\\Idle_PowerUp.png', 'Idle_PowerUp', 6)
        self.Animation_Player_PowerUp.set_sprite('Resource\\Graphics\\Sprite\\Player\\Attack_Punch_PowerUp.png', 'Attack_Punch_PowerUp', 4)
        self.Animation_Player_PowerUp.set_sprite('Resource\\Graphics\\Sprite\\Player\\PowerDown.png', 'PowerDown', 5)
        # Set Animation State
        self.Animation_Player_PowerUp.set_state('Idle_PowerUp', 6, 0, 6, 6, 6)
        self.Animation_Player_PowerUp.set_state('Attack_Punch_PowerUp', 4, 0, 1, 2, 4)
        self.Animation_Player_PowerUp.set_state('PowerDown', 5, 0, 0, 0, 5)
        # Set Animation Delay
        self.Animation_Player_PowerUp.set_state_delay('Idle_PowerUp', 6, 1, 1)
        self.Animation_Player_PowerUp.set_state_delay('Attack_Punch_PowerUp', 3, 3, 3)
        self.Animation_Player_PowerUp.set_state_delay('PowerDown', 1, 1, 5)