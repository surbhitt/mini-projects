#!/usr/bin/env python -tt

import pygame
import os

# window's properties
WIDTH, HEIGHT = 1200, 590
WIN = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("HUMMHOP")

# color parameters
WHITE = (255, 255, 255)
AXIS_BROWN = (234,182,118)

FPS = 60
ACTIVITY_AXIS_CORD = 460


# object attributes
SUBJECT_WIDTH = 175
SUBJECT_LENGTH = 200
OBSTACLE_WIDTH = 200
OBSTACLE_LENGTH = 150

# object loading/transformation
SUBJECT_IMAGE = pygame.image.load(os.path.join('assets','hummingbird.png'))
SUBJECT = pygame.transform.scale(SUBJECT_IMAGE, (SUBJECT_WIDTH, SUBJECT_LENGTH))
OBSTACLE_IMAGE = pygame.image.load(os.path.join('assets','lotus.png'))
OBSTACLE = pygame.transform.scale(OBSTACLE_IMAGE, (OBSTACLE_WIDTH, OBSTACLE_LENGTH))

# THE BASE LINE pygame.rect(x_cord, y_cord, width, height,)
BASE =  pygame.Rect(0, ACTIVITY_AXIS_CORD, WIDTH, 25)

# function to draw all the elements
def draw_window(OBSTACLE_POS, SUBJECT_INST_Y):
    # window background fill
    WIN.fill(WHITE)

    # object setup 
    pygame.draw.rect(WIN, AXIS_BROWN, BASE)
    WIN.blit(OBSTACLE, (OBSTACLE_POS, ACTIVITY_AXIS_CORD-70))
    WIN.blit(SUBJECT, (125, SUBJECT_INST_Y))
   

    pygame.display.update()



# main function
def main():

    clock = pygame.time.Clock()

    # variables (local declaration)------------------------------
    run = True
    isJUMP = False          # the jump variable
    jumpcount = 10
    OBSTACLE_SPEED = 8
    OBSTACLE_POS = WIDTH
    SUBJECT_INST_Y = ACTIVITY_AXIS_CORD-130

    # game loop--------------------------------------------------
    while run:
        clock.tick(FPS)

        if OBSTACLE_POS == WIDTH:
            var_obs_pos = OBSTACLE_WIDTH + WIDTH
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
        
        # for the jumping mechanism------------------------------
        keys = pygame.key.get_pressed()     # registering keypress
        if not(isJUMP):
            if keys[pygame.K_SPACE]:
                isJUMP = True
        else:
            if jumpcount >= -10:
                neg = 1
                if jumpcount < 0:
                    neg = -1
                SUBJECT_INST_Y -= (jumpcount ** 2) * 0.5 * neg
                jumpcount -= 0.5
            else:
                isJUMP = False
                jumpcount = 10

        # call for the draw function-----------------------------
        draw_window(OBSTACLE_POS, SUBJECT_INST_Y)
        
        # obstacle movement--------------------------------------
        OBSTACLE_POS -= OBSTACLE_SPEED
        var_obs_pos -= OBSTACLE_SPEED
        if var_obs_pos < 0:
            OBSTACLE_POS = WIDTH

    pygame.quit()      


# boiler plate (the main() will not be executed if this file is not directely accesed)
if __name__ == "__main__":
    main()