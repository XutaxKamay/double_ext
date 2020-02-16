#include <sourcemod>
#include <double>

public void OnPluginStart()
{
	Double data;
	char buffer[256];

	// public static native Double FromString(char[] value);
	{
		data = Double.FromString("3.141592653589793238462643383279502884197169399375105820974944592307816406");
		
		data.ToString(buffer, 256);
		PrintToConsoleAll("got: %s, expected: %s", buffer, "3.141592653589793238462643383279502884197169399375105820974944592307816406");
	}

	// public static native Double FromInt(int value);
	{
		data = Double.FromInt(123456789);
		
		data.ToString(buffer, 256);
		PrintToConsoleAll("got: %s, expected: %s", buffer, "123456789");
	}

	// public static native Double FromFloat(float value);
	{
		data = Double.FromFloat(1234.34567);
		
		data.ToString(buffer, 256);
		PrintToConsoleAll("got: %s, expected: 1234.34567", buffer);
	}

	// public native int ToInt();
	// public native float ToFloat();
	{
		data = Double.FromString("3.141592653589793238462643383279502884197169399375105820974944592307816406");
		
		PrintToConsoleAll("got: int %i float %f expected: %s", data.ToInt(), data.ToFloat(), "3.141592653589793238462643383279502884197169399375105820974944592307816406");
	}

	// public static native bool GreaterThan(Double left, Double right);
	// public static native bool LessThan(Double left, Double right);
	// public static native bool EqualTo(Double left, Double right);
	{
		Double four = Double.FromInt(4);
		Double pi = Double.FromString("3.141592653589793238462643383279502884197169399375105820974944592307816406");
		PrintToConsoleAll
		(
			"four > pi == %b\n" ...
			"pi == pi == %b\n" ...
			"four < pi == %b",
			four > pi,
			data == pi,
			four < pi
		);
	}


	// public native void AbsoluteRef();
	// public static native Double Absolute(Double value);
	{
		Double negativeFive = Double.FromInt(-5);
		Double positiveFive = Double.Absolute(negativeFive);
		Double negative = negativeFive.Clone();
		PrintToConsoleAll("abs got: %f %f %f\nabs exp: -5.0 5.0, 5.0", negativeFive.ToFloat(), positiveFive.ToFloat(), negative.AbsoluteRef().ToFloat());
	}

	
	// public native Double Clone();
	// public native void ModuloRef(Double denominator);
	// public static native Double Modulo(Double number, Double denominator);
	{
		Double twentyfive = Double.FromInt(25);
		Double onetwentyfive = Double.FromInt(125);
		Double onetwentyfive2 = onetwentyfive.Clone();
		Double onetwentyfive3 = onetwentyfive.Clone();
		PrintToConsoleAll("mod got: %f %f %f", onetwentyfive.ToFloat(), onetwentyfive2.ModuloRef(twentyfive).ToFloat(), Double.Modulo(onetwentyfive3, twentyfive).ToFloat());
		PrintToConsoleAll("mod exp: %f %f %f", float(125), float(125 % 25), float(125 % 25));
	}

	// public native void AddRef(Double right);
	// public static native Double Add(Double left, Double right);
	{
		Double ten = Double.FromInt(10);
		Double twenty = Double.Add(ten, ten);
		Double thirty = twenty.Clone();
		thirty.AddRef(ten);

		PrintToConsoleAll("add got: %f %f %f", twenty.ToFloat(), thirty.ToFloat(), Double.Add(twenty, twenty).ToFloat());
		PrintToConsoleAll("add exp: 20.0 30.0 40.0");
	}

	// public native void SubtractRef(Double right);
	// public static native Double Subtract(Double left, Double right);
	{
		Double ten = Double.FromInt(10);
		Double five = Double.FromInt(5);

		Double zero = five.Clone();
		zero.SubtractRef(five);

		Double negativeFive = Double.Subtract(zero, ten);

		PrintToConsoleAll("sub got: %f %f %f", five.ToFloat(), zero.ToFloat(), negativeFive.ToFloat());
		PrintToConsoleAll("sub exp: 5.0 0.0 -10.0");
	}

	// public native void MultiplyRef(Double right);
	// public static native Double Multiply(Double left, Double right);
	{
		Double five = Double.FromInt(5);
		Double twentyfive = Double.Multiply(five, five);
		Double zero = Double.FromInt(0);
		zero.MultiplyRef(twentyfive);
		PrintToConsoleAll("mult got: %f %f %f", five.ToFloat(), twentyfive.ToFloat(), zero.ToFloat());
		PrintToConsoleAll("mult exp: 5.0 25.0 0.0");
	}
	

	// public native void DivideRef(Double right);
	// public static native Double Divide(Double left, Double right);
	{
		Double three = Double.FromInt(3);
		Double ten = Double.FromInt(10);

		Double third = Double.Divide(ten, three);

		ten = third.Clone().DivideRef(third);
		Double zero = Double.FromInt(0);
		Double nan = Double.Divide(ten, zero);

		PrintToConsoleAll("div got: %f %f %f IsNaN: %b", third.ToFloat(), ten.ToFloat(), nan.ToFloat(), nan.IsNaN);
		PrintToConsoleAll("div exp: 3.33333333333 1.0 NaN IsNaN: 1");
	}
		
	// public native void PowRef(Double right);
	// public static native Double Pow(Double left, Double right);
	{
		Double three = Double.FromInt(3);
		Double ten = Double.FromInt(10);
		Double negativeTen = Double.FromInt(-10);
		Double thousand = Double.Pow(ten, three);

		Double small = ten.Clone().PowRef(negativeTen);
		PrintToConsoleAll("pow got: %f %f", thousand.ToFloat(), small.ToFloat());
		PrintToConsoleAll("pow exp: 1000.0 0.0000000001");
	}
	
	// public native void SquareRootRef();
	// public static native Double SquareRoot(Double right);
	{
		Double ten = Double.FromInt(10);
		Double negativeOne = Double.FromInt(-1);
		Double sqrtTen = Double.SquareRoot(ten);
		Double fourRootTen = sqrtTen.Clone().SquareRootRef();
		Double nan = Double.SquareRoot(negativeOne);


		PrintToConsoleAll("sqrt: %f %f nan: %f IsNaN: %b", sqrtTen.ToFloat(), fourRootTen.ToFloat(), nan.ToFloat(), nan.IsNaN);
		PrintToConsoleAll("sqrt: 3.16227766017 1.77827941004 NaN: 0.0 IsNaN: 1");
	}

}