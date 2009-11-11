public class Hello
{

	public static void Main()
	{
		double f = 10.23242;
		double v = 234.2343;
		System.Console.WriteLine("floating point value = {0}", f*v);
        for (int i=0; i < 10; i++) {
            v += 0.23;
            System.Console.WriteLine("next inc = {0}", f*v);
        }
	}
}

	
