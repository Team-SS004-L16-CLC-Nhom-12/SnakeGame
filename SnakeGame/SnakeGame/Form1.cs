using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Media;


namespace SnakeGame
{
    public partial class Form1 : Form
    {
        Game thegame = new Game();
      


        public void DrawGame(Game game)
        {
            //draw head
            PictureBox headpic = new PictureBox();
            headpic.Location = new Point(game.snake.head.x * 10, game.snake.head.y * 10);
            headpic.Size = new Size(10, 10);
            switch (game.snake.head.direction)
            {
                case Directions.left:
                    {
                        headpic.Image = new Bitmap(SnakeGame.Properties.Resources.headLeft);
                        break;
                    }
                case Directions.right:
                    {
                        headpic.Image = new Bitmap(SnakeGame.Properties.Resources.headRight);
                        break;
                    }
                case Directions.up:
                    {
                        headpic.Image = new Bitmap(SnakeGame.Properties.Resources.headUp);
                        break;
                    }
                case Directions.down:
                    {
                        headpic.Image = new Bitmap(SnakeGame.Properties.Resources.headDown);
                        break;
                    }
            }
            panel1.Controls.Add(headpic);
            //draw bodies
            for (int i = 0; i < game.snake.Length - 1; i++)
            {
                PictureBox bodypic = new PictureBox();
                bodypic.Location = new Point(game.snake.bodies[i].x * 10, game.snake.bodies[i].y * 10);
                bodypic.Size = new Size(10, 10);





                switch (game.snake.bodies[i].stat)
                {
                    case BodyStatic.horizontal:
                        bodypic.Image = new Bitmap(SnakeGame.Properties.Resources.verticalBody);
                        break;
                    case BodyStatic.vertical:
                        bodypic.Image = new Bitmap(SnakeGame.Properties.Resources.horizontalBody);
                        break;
                    case BodyStatic.topright:
                        bodypic.Image = new Bitmap(SnakeGame.Properties.Resources.topright);
                        break;
                    case BodyStatic.lefttop:
                        bodypic.Image = new Bitmap(SnakeGame.Properties.Resources.topleft);
                        break;
                    case BodyStatic.bottomleft:
                        bodypic.Image = new Bitmap(SnakeGame.Properties.Resources.botleft);
                        break;
                    case BodyStatic.bottomright:
                        bodypic.Image = new Bitmap(SnakeGame.Properties.Resources.botright);
                        break;

                }

                panel1.Controls.Add(bodypic);

            }
            // draw food
            PictureBox foodpic = new PictureBox();
            foodpic.Location = new Point(game.food.x * 10, game.food.y * 10);
            foodpic.Size = new Size(10, 10);
            foodpic.Image = new Bitmap(SnakeGame.Properties.Resources.food);
            panel1.Controls.Add(foodpic);
        }

        public void DrawBlood(Snake snake)
        {
            PictureBox bloodbox = new PictureBox();
            bloodbox.Location = new Point(snake.head.x * 10, snake.head.y * 10);
            bloodbox.Size = new Size(10, 10);
            bloodbox.Image = new Bitmap(SnakeGame.Properties.Resources.bloodSnake);
            panel1.Controls.Add(bloodbox);
            
            for(int i = 0; i < snake.Length-1; i++)
            {
                PictureBox bloodbody = new PictureBox();
                bloodbody.Location = new Point(snake.bodies[i].x * 10, snake.bodies[i].y * 10);
                bloodbody.Size = new Size(10, 10);
                bloodbody.Image = new Bitmap(SnakeGame.Properties.Resources.bloodSnake);
                panel1.Controls.Add(bloodbody);
            }

        }
        public void refreshScreen()
        {
            panel1.Controls.Clear();
        }

        public void endTheGame(bool isOver)
        {
            if (isOver)
            {

                
                thegame.Score = 0;
                thegame.inGame = false;
                timer1.Stop();
                thegame.refresh();
                DrawBlood(thegame.snake);
                Thread.Sleep(1000);
                TextBox ndeath = new TextBox();
                ndeath.Enabled = false;
                ndeath.Text = "The game was over, click on me to revive the snake";
                ndeath.Location = new Point(100, 25);
                panel1.Controls.Add(ndeath);
                PictureBox death = new PictureBox();
                death.Location = new Point(100, 100);
                death.Size = new Size(400, 200);
                death.Image = new Bitmap(SnakeGame.Properties.Resources.devil);
                death.SizeMode = PictureBoxSizeMode.StretchImage;
                death.Click += Death_Click;
                panel1.Controls.Add(death);
            }
            
            
        }

        public void reset()
        {
            timer1.Stop();
            thegame = new Game();
            thegame.inGame = false;
            thegame.draw = DrawGame;
            thegame.refresh = refreshScreen;
            thegame.refresh();
            thegame.game_over = endTheGame;
        }

        private void Death_Click(object sender, EventArgs e)
        {
            reset();
        }

        public Form1()
        {
            InitializeComponent();
            thegame.inGame = false;
            thegame.draw = DrawGame;
            thegame.refresh = refreshScreen;
            thegame.game_over = endTheGame;
        }



        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            bool bHandled = false;

            if (thegame.inGame == true)
            {
                switch (keyData)
                {
                    case Keys.Right:
                        thegame.snake.head.Turn(Directions.right);
                        bHandled = true;
                        break;
                    case Keys.Left:
                        thegame.snake.head.Turn(Directions.left);
                        bHandled = true;
                        break;
                    case Keys.Up:
                        thegame.snake.head.Turn(Directions.up);
                        bHandled = true;
                        break;
                    case Keys.Down:
                        thegame.snake.head.Turn(Directions.down);
                        bHandled = true;
                        break;
                }
            }
            
            return bHandled;
        }







        private void pictureBox1_Click(object sender, EventArgs e)
        {
            reset();
        }

        private void playBtn_Click(object sender, EventArgs e)
        {   
            if((string)comboBox1.Text == "")
            {
                MessageBox.Show("Please enter difficulty");
                return;
            }
            if ((string)comboBox1.Text == "Easy")
            {
                timer1.Interval = 500;
                thegame.incScore = 1;
            }
            if ((string)comboBox1.Text == "Medium")
            {
                timer1.Interval = 250;
                thegame.incScore = 2;
            }
            if ((string)comboBox1.Text == "Hard")
            {
                timer1.Interval = 100;
                thegame.incScore = 16;
            }
            thegame.inGame = true;
            timer1.Start();
            
        }

        private void timer1_Tick(object sender, EventArgs e)
        {

            thegame.operate();
            label1.Text = "Score : " + thegame.Score;
            label2.Text = "High Score : " + thegame.HighScore;
            
        }

        private void Form1_KeyPress(object sender, KeyPressEventArgs e)
        {
            MessageBox.Show(e.KeyChar.ToString());
        }

        

        private void button1_Click(object sender, EventArgs e)
        {
            reset();
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
