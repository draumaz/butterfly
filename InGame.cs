using System;
using System.IO;
using System.Threading;
using Game_Data;
using Global;
using Hypersurf;
using File_Processing;

namespace InGame
{
    internal class InBattle
    {
        public void Battle_Options()
        {
            Hypersurf.Surfer surf = new();
            Global.Friends fr = new();
            Random ran = new();
            int shake = ran.Next(1, 26);
            var IO = new File_Processing.IO();
            int[] x = IO.Save_Read();
            int Enemy_Health_Affected;
            int Item_Did_Action;
            int Spare_Did_Work;
            int Health = x[1];
            int Strength = x[2];
            int Enemy_Race_Int = x[3];
            int Enemy_Health = x[4];
            int Enemy_Strength = x[5];
            int Use_Potion = x[6];
            int Use_Spear = x[7];
            Console.WriteLine("\nFIGHT [1]\nITEMS [2]\nSPARE [3]\n");
            int i = IO.User_Input(1, 3);
            surf.False_Hopper(Convert.ToString(i));
            switch (i)
            {
                case 1:
                    if (shake == 17)
                    {
                        break;
                    }
                    break;
                case 2:
                    break;
                case 3:
                    break;
            }
        }
        public void Battle_Header()
        {
            var IO = new File_Processing.IO();
            var CH = new Game_Data.Character_Data();
            int[] a = IO.Save_Read();
            int[] b = IO.Record_Read();
            int Player_Race_Int = a[0];
            int Player_Health = a[1];
            int Player_Strength = a[2];
            int Enemy_Race_Int = a[3];
            int Enemy_Health = a[4];
            int Enemy_Strength = a[5];
            string[] c = CH.Enemy_Race_Get(Enemy_Race_Int);
            string d = CH.Player_Race_Get(Player_Race_Int);
            if (a[1] < 0)
            {
                a[1] = 0;
            }
            if (a[4] < 0)
            {
                a[4] = 0;
            }
            Console.WriteLine("\nButterfly v0.04 | KILLS: {0} | DEATHS: {1} | SPARES: {2}", b[0], b[1], b[2]);
            Console.WriteLine("\nYOU: {0} | HP: {1} | STR: {2}", d, Player_Health, Player_Strength);
            Console.WriteLine("ENEMY: {0} | HP: {1} | STR: {2}", c[0], Enemy_Health, Enemy_Strength);
        }
    }
    internal class PreBattle
    {
        public void Play_Again()
        {
            File_Processing.IO IO = new();
            Console.WriteLine("\nPlay again?\n\nYES [1]\nNO [2]\n");
            int i = IO.User_Input(1, 2);
        }
        public void Conditions()
        {
            var IO = new File_Processing.IO();
            int[] x = IO.Save_Read();
            int Player_Health = x[1];
            int Enemy_Health = x[4];
            if (Player_Health < 0)
            {
                Player_Health = 0;
            }
            if (Enemy_Health < 0)
            {
                Enemy_Health = 0;
            }
            if (Player_Health <= 0)
            {
                if (Enemy_Health > 0)
                {
                    int line = 1;
                    IO.Record_Write(line);
                    Console.WriteLine("\nYou died!");
                    File.Delete("temp.txt");
                    // TODO
                }
                if (Enemy_Health <= 0)
                {
                    Console.WriteLine("\nAn old-fashioned stalemate...");
                    File.Delete("temp.txt");
                    // TODO
                }
            }
            if (Enemy_Health <= 0)
            {
                if (Player_Health > 0)
                {
                    // Win
                }
            }
        }
    }
}