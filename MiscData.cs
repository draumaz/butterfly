using System;
using System.IO;
using System.Text;
using System.Linq;
using System.Threading;
using Hypersurf;
using File_Processing;

namespace Game_Data
{
    internal class Fake_Surf
    {
        public void Surf_One(string Action_Num)
        {
            Console.WriteLine("ACTION >> {0}", Action_Num);
        }
    }
    internal class Character_Data
    {
        public string Player_Race_Get(int Player_Race_Int)
        {
            string Player_Race = "";
            switch (Player_Race_Int)
            {
                case 1:
                    Player_Race = "Vuleen";
                    break;
                case 2:
                    Player_Race = "Aradi";
                    break;
                case 3:
                    Player_Race = "Human";
                    break;
            }
            return Player_Race;
        }
        public string[] Enemy_Race_Get(int Enemy_Race_Int)
        {
            string[] i = new string[2];
            string x = "";
            switch (Enemy_Race_Int)
            {
                case 1:
                    x = "arak";
                    i[0] = "D" + x;
                    i[1] = "d" + x;
                    break;
                case 2:
                    x = "oblin";
                    i[0] = "G" + x;
                    i[1] = "g" + x;
                    break;
                case 3:
                    x = "rcran";
                    i[0] = "A" + x;
                    i[1] = "a" + x;
                    break;
                case 4:
                    i[0] = "ULTRA GOBLIN";
                    i[1] = i[0];
                    break;
            }
            return i;
        }
        public static int[] Stats_Info_Get()
        {
            Random ran = new();
            IO io = new();
            int[] vars = io.Save_Read();
            int Enemy_Random = ran.Next(1, 3);
            int Player_Random = ran.Next(1, 3);
            int Goblin_Random = ran.Next(0, 15);
            int Player_Race = 0;
            int Player_Health = 0;
            int Player_Strength = 0;
            int Enemy_Race = 0;
            int Enemy_Health = 0;
            int Enemy_Strength = 0;
            int Use_Potion = 0;
            int Use_Spear = 0;
            if (Player_Random == 1)
            {
                Player_Race = 1;
                Player_Health = 20;
                Player_Strength = 10;
            }
            if (Player_Random == 2)
            {
                Player_Race = 2;
                Player_Health = 30;
                Player_Strength = 15;
            }
            if (Player_Random == 3)
            {
                Player_Race = 3;
                Player_Health = 20;
                Player_Strength = 7;
            }
            if (Enemy_Random == 1)
            {
                Enemy_Race = 1;
                Enemy_Health = 25;
                Enemy_Strength = 10;
            }
            if (Enemy_Random == 2)
            {
                Enemy_Race = 2;
                Enemy_Health = 12;
                Enemy_Strength = 7;
                if (Goblin_Random == 12)
                {
                    Enemy_Race = 4;
                    Enemy_Health = 40;
                    Enemy_Strength = 15;
                }
            }
            if (Enemy_Random == 3)
            {
                Enemy_Race = 3;
                Enemy_Health = 30;
                Enemy_Strength = 5;
            }
            vars[0] = Player_Race;
            vars[1] = Player_Health;
            vars[2] = Player_Strength;
            vars[3] = Enemy_Race;
            vars[4] = Enemy_Health;
            vars[5] = Enemy_Strength;
            vars[6] = Use_Potion;
            vars[7] = Use_Spear;
            return vars;
        }
        public void Stats_Populate()
        {
            Global.Config cfg = new();
            int m = 1;
            int[] read_array = Stats_Info_Get();
            string[] write_array = read_array.Select(x => x.ToString()).ToArray();
            File.WriteAllLines(cfg.Paths(m), write_array);
        }
    }
}