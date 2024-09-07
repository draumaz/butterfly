using System;
using System.IO;
using System.Linq;
using System.Threading;
using Game_Data;
using Hypersurf;

namespace File_Processing
{
    internal class IO
    {
        Hypersurf.Surfer surf = new();
        Global.Config cfg = new();
        Global.Friends frn = new();
        Character_Data chd = new();
        string ii;
        int i;
        public int User_Input(int a, int b)
        {
            
            while (true)
            {
                Console.Write("ACTION >> ");
                try
                {
                    ii = Console.ReadLine();
                    i = Convert.ToInt32(ii);
                    if (i < a || i > b)
                    {
                        if (i == 420 || i == 69)
                        {
                            Console.WriteLine("\nBased.");
                            Thread.Sleep(500);
                        }
                        else
                        {
                            frn.Input_Error_Handler();
                        }
                        Console.Clear();
                        surf.Hopper();
                        continue;
                    }
                    break;
                }
                catch (System.FormatException)
                {
                    surf.False_Hopper(ii);
                    frn.Input_Error_Handler();
                    Console.Clear();
                    surf.Hopper();
                    continue;
                }
            }
            return i;
        }
        public int Exists_Temp()
        {
            int m = 1;
            bool x = File.Exists(cfg.Paths(m));
            if (x == true)
            {
                return 0;
            }
            if (x == false)
            {
                Save_Gen();
                chd.Stats_Populate();
                return 0;
            }
            return 1;
        }
        public int Exists_Record()
        {
            int m = 3;
            bool x = File.Exists(cfg.Paths(m));
            if (x == true)
            {
                return 0;
            }
            if (x == false)
            {
                Record_Gen();
                return 0;
            }
            return 1;
        }
        public int[] Save_Read()
        {
            int m = 1;
            string[] x = File.ReadAllLines(cfg.Paths(m));
            int[] y = Array.ConvertAll(x, int.Parse);
            return y;
        }
        public void Save_Write(int line, int state)
        {
            int m = 1;
            int[] read_array = Save_Read();
            read_array[line] = state;
            string[] write_array = read_array.Select(x => x.ToString()).ToArray();
            File.WriteAllLines(cfg.Paths(m), write_array);
        }
        public void Save_Gen()
        {
            int m = 1;
            int mm = 2;
            string sl = cfg.Paths(m);
            string sp = cfg.Paths(mm);
            File.WriteAllText(sl, sp);
        }
        public int[] Record_Read()
        {
            int m = 3;
            string[] x = File.ReadAllLines(cfg.Paths(m));
            int[] y = Array.ConvertAll(x, int.Parse);
            return y;
        }
        public void Record_Write(int line)
        {
            int m = 3;
            int[] arr = Record_Read();
            arr[line] += 1;
            string[] arr_out = arr.Select(x => x.ToString()).ToArray();
            File.WriteAllLines(cfg.Paths(m), arr_out);
        }
        public void Record_Gen()
        {
            int m = 3;
            string sl = cfg.Paths(m);
            File.WriteAllText(sl, "0\n0\n0");
        }
    }
}