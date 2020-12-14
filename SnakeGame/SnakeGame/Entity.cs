using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SnakeGame
{
    


    public abstract class Entity
    {
        public int x;
        public int y;
        public int x0;
        public int y0;

        public Directions direction;
        public Directions predirection;
        public EntityType type;

        public void setCrood(int x,int y)
        {
            this.x = x;
            this.y = y;
        }
        public bool check(Entity ent)
        {
            if (this.x == ent.x && this.y == ent.y)
                return true;
            return false;
        }
    }

    public class SnakeHead : Entity
    {   
        

        public EntityEvent HeadEvent;
        public SnakeHead()
        {
            x = 6;
            y = 3;
            x0 = 5;
            y0 = 3;
            direction = Directions.right;
            predirection = Directions.right;

            type = EntityType.Head;
            HeadEvent = EntityEvent.Living;
        }
        public void Turn(Directions moving) // Hàm cho đầu con rắn đổi hướng
        {
            switch (moving)
            {
                case Directions.left:
                    { if (direction != Directions.right)
                        {
                            direction = Directions.left;
                        }
                        break; 
                    }

                case Directions.right:
                    { 
                    if (direction != Directions.left)
                    {
                        direction = Directions.right;
                    }
                    break; 
                    }
            
                case Directions.up: 
                { 
                    if (direction != Directions.down)
                    {
                        direction = Directions.up;
                    }
                    break;
                }
                case Directions.down: 
                    {
                        if (direction != Directions.up)
                        {
                            direction = Directions.down;
                        }
                        break; 
                    }
            }
        }

        public void GoAhead() // Hàm cho con rắn đi tới
        {
            switch(this.direction)
            {
                case Directions.left: { x--;break; }
                case Directions.right: { x++; break; }
                case Directions.up: { y--; break; }
                case Directions.down: { y++; break; }
            }
        }

        

        
        
    }

    public class SnakeBody:Entity
    {
        public BodyStatic stat = BodyStatic.horizontal;
        
        public SnakeBody()
        {
            type = EntityType.Body;
        }
        

        public void setStatic(Entity prebody, Entity nextbody)
        {
            if((prebody.y == y && prebody.x < x && nextbody.y == y && nextbody.x > x) || (nextbody.y == y && nextbody.x < x && prebody.y == y && prebody.x > x))
            {
                stat = BodyStatic.horizontal;
            }
            
            
            if ((prebody.x == x && prebody.y < y && nextbody.x == x && nextbody.y > y)|| (nextbody.x == x && nextbody.y < y && prebody.x == x && prebody.y > y))
            {
                stat = BodyStatic.vertical;
            }
            if ((prebody.x < x && prebody.y == y && nextbody.x == x && nextbody.y < y) || (nextbody.x < x && nextbody.y == y && prebody.x == x && prebody.y < y))
            {
                stat = BodyStatic.lefttop;
            }
           
            if ((prebody.y == y && prebody.x > x && nextbody.x == x && nextbody.y < y) || (nextbody.y == y && nextbody.x > x && prebody.x == x && prebody.y < y))
            {
                stat = BodyStatic.topright;
            }
            
            if ((prebody.y == y && prebody.x > x && nextbody.x == x && nextbody.y > y) || (nextbody.y == y && nextbody.x > x && prebody.x == x && prebody.y > y))
            {
                stat = BodyStatic.bottomright;
            }
            
            if ((prebody.y == y && prebody.x < x && nextbody.y > y && nextbody.x == x) || (nextbody.y == y && nextbody.x < x && prebody.y > y && prebody.x == x))
            {
                stat = BodyStatic.bottomleft;
            }
            
        }
        public void setStatic()
        {
            if((direction == Directions.left && predirection == Directions.left)||(direction == Directions.right && predirection == Directions.right))
            {
                stat = BodyStatic.horizontal;
            }
            if ((direction == Directions.up && predirection == Directions.up) || (direction == Directions.down && predirection == Directions.down))
            {
                stat = BodyStatic.vertical;
            }
            if ((direction == Directions.up && predirection == Directions.right) || (direction == Directions.left && predirection == Directions.down))
            {
                stat = BodyStatic.lefttop;
            }
            if ((direction == Directions.right && predirection == Directions.down)|| (direction == Directions.up && predirection == Directions.left))
            {
                stat = BodyStatic.topright;
            }
            if ((direction == Directions.left && predirection == Directions.up) || (direction == Directions.down && predirection == Directions.right))
            {
                stat = BodyStatic.bottomleft;
            }
            if ((direction == Directions.right && predirection == Directions.up) || (direction == Directions.down && predirection == Directions.left))
            {
                stat = BodyStatic.bottomright;
            }
        }


    }

    public class Food: Entity
    {
        
        public Food()
        {
            
            type = EntityType.Food;
        }
        
    }

    public class Snake
    {
        public SnakeHead head = new SnakeHead();
        public int Length = 4;
        public List<SnakeBody> bodies = new List<SnakeBody>();

        public Snake(int x, int y)
        {
            head.x = x;
            head.y = y;
            head.direction = Directions.right;

            for(int i = 0; i < Length; i ++)
            {
                SnakeBody newpart = new SnakeBody();
                newpart.setCrood(x - 1 - i,y);
                newpart.direction = Directions.right;
                
                
                
                    newpart.stat = BodyStatic.horizontal;
                
                bodies.Add(newpart);
            }
        }
        public bool eat(Food food)
        {
            if (head.x == food.x && head.y == food.y)
            {
                
                this.increaseLength();
                return true;
            }
            else return false;

        }

        public void prepareMovement()
        {
            head.x0 = head.x;
            head.y0 = head.y;
            head.predirection = head.direction;
            for(int i = 0; i < Length; i++)
            {
                bodies[i].x0 = bodies[i].x;
                bodies[i].y0 = bodies[i].y;
                bodies[i].predirection = bodies[i].direction;
                
            }
        }
        public void goAhead()
        {
            
            head.GoAhead();
            bodies[0].x = head.x0;
            bodies[0].y = head.y0;
            bodies[0].direction = head.predirection;
            
            for (int i = 1;i < Length; i++)
            {
                bodies[i].x = bodies[i - 1].x0;
                bodies[i].y = bodies[i - 1].y0;
                bodies[i].direction = bodies[i - 1].predirection;
                
            }

            bodies[0].setStatic(head, bodies[1]);
            
            for (int i = 1; i < Length; i++)
            {

                if (i != Length - 1)
                    bodies[i].setStatic(bodies[i - 1], bodies[i + 1]);
                else
                    bodies[i].setStatic();
                
            }
            prepareMovement();
        }



        

        

        public void increaseLength()
        {
            SnakeBody newbody = new SnakeBody();

            newbody.x = bodies[Length - 1].x0;
            newbody.y = bodies[Length - 1].y0;
            bodies.Add(newbody);
            Length++;

        }

        public Snake resetSnake()
        {
            Snake snake = new Snake(5, 3);
            return snake;
        }
    }
    
   
    public class Game
    {
        public int Score;
        public int HighScore;
        public int incScore = 0;
        public bool inGame = false;

        public Snake snake;
        public Food food = new Food();
        

        public Game()
        {
            snake = new Snake(5, 3);
            generateFood();
        }
        void generateFood()
        {
            Random rand = new Random();
            int newX = rand.Next(0, 59);
            int newY = rand.Next(0, 59);

            if(newX == snake.head.x && newY == snake.head.y) // check xem food có trùng với rắn ko, nếu trùng phải tạo lại
            {
                newX = rand.Next(0, 59);
                newY = rand.Next(0, 59);
            }
            for(int i = 0; i < snake.Length - 1; i++)
            {
                if(newX == snake.bodies[i].x && newY == snake.bodies[i].y)
                {
                    newX = rand.Next(0, 59);
                    newY = rand.Next(0, 59);
                }
            }
            food.x = newX;
            food.y = newY;
        }
        

        // init the game
        public void init()
        {
            Score = 0;
            snake = new Snake(5, 3);
            generateFood();
        }

        // operate the game
        public delegate void drawGame(Game game);
        public drawGame draw;
        public delegate void Refresh();
        public Refresh refresh;
        
        public void operate()
        {
            refresh();
            draw(this);
            this.snake.goAhead();
            if(snake.eat(food))
            {
                Score += incScore;
                if (Score > HighScore)
                    HighScore = Score;
                   
                generateFood();
            }
            endGame();
        }







        // end the game
        public bool checkGameOver()
        {
            if (snake.head.x > 60 || snake.head.y > 60 || snake.head.x < -1 || snake.head.y < -1)
                return true;
            for(int i = 0; i < snake.Length - 1; i ++)
            {
                if(snake.head.check(snake.bodies[i]))
                {
                    return true;
                }
            }
            return false;
        }

        public delegate void gameOver(bool isOver);
        public gameOver game_over;

        public void endGame()
        {
            game_over(checkGameOver());
            
        }


    }

}
