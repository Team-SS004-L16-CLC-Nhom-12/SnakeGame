using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SnakeGame
{
    public enum Directions
    {
        left,
        right,
        up,
        down,
    }


    public enum BodyStatic
    {   
        vertical,
        horizontal,
        lefttop,
        topright,
        bottomright,
        bottomleft,
    }
     public enum TailStatic
    {   none,
        left,
        right,
        up,
        down,
    }


    public enum EntityType
    {
        Head,
        Body,
        Food,
        Obstacle,
    }
    public enum EntityEvent
    {   
        Living,
        Eat,
        Collide,
    }
}
