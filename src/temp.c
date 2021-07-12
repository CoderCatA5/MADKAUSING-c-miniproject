switch (Game_Window)
        {
        case 3:
            Draw_Pong(&player1, &player2, red1, red2, blue1, blue2, &ball, bricks);
            break;

        case 2:
            mousePoint = GetMousePosition();
            
            BeginDrawing();
            ClearBackground(BLACK);
            if (!check_win_condition(&g) && g.round < 9)
            {
                check_button(b, &g, mousePoint, Cross, Nought);
                //Draws a grid of red lines marking the board
                make_grid(b, WindowWidth, WindowHeight, grid_texture);
                switch (g.round % 2)
                {
                case 0:
                    DrawText("Player 1's turn", 300, 200, 30, BLUE);
                    break;
                case 1:
                    DrawText("Player 2's turn", 1100, 200, 30, GREEN);
                    break;
                }
                // check_win_condition(&g);
                //if(check_win_condition(&g)) break;
            }
            else
            {
                switch (g.winner)
                {
                case 0:
                    DrawText("It's a draw.", 700, 450, 30, YELLOW);
                    break;
                case 1:
                    DrawText("Player 1 wins.", 700, 450, 30, BLUE);
                    break;
                case 2:
                    DrawText("Player 2 wins.", 700, 450, 30, GREEN);
                    break;
                }
            }
            EndDrawing();
        }
        break;
    }
    UnloadTexture(Cross);
    UnloadTexture(Nought);
    UnloadTexture(grid_texture);
    UnloadTexture(blank);