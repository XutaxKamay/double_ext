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
		Double denom = Double.FromInt(25);
		Double simpleMod = Double.FromInt(125);
		Double cloned = simpleMod.Clone();
		PrintToConsoleAll("mod got: %f %f %f", simpleMod.ToFloat(), simpleMod.ModuloRef(denom).ToFloat(), Double.Modulo(cloned, denom).ToFloat());
		PrintToConsoleAll("mod exp: %f %f %f", float(125), float(125 % 25), float(125 % 25));
	}

	// public native void AddRef(Double right);
	// public static native Double Add(Double left, Double right);
	{
		Double ten = Double.FromInt(10);
		Double twenty = Double.Add(ten, ten);
		Double thirty = twenty.Clone();
		thirty.AddRef(ten);

		PrintToConsoleAll("add got: %f %f %f", twenty.ToFloat(), thirty.ToFloat(), Double.Add(five, five).ToFloat());
		PrintToConsoleAll("add exp: 20.0 30.0 10.0");
	}

	// public native void SubstractRef(Double right);
	// public static native Double Substract(Double left, Double right);
	{
		Double five = Double.FromInt(5);

		Double zero = five.Clone();
		zero.SubstractRef(five);

		Double negativeFive = Double.Substract(ten, ten);
		Double thirty = twenty.Clone();

		PrintToConsoleAll("sub got: %f %f %f", five.ToFloat(), five.SubstractRef(five).ToFloat(), Double.Substract(five, Double.FromInt(25)).ToFloat());
		PrintToConsoleAll("sub exp: 5.0 30.0 10.0");
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

		Double nan = Double.Divide(ten, zero);

		PrintToConsoleAll("mult got: %f %f %f IsNaN: %b", third.ToFloat(), ten.ToFloat(), nan.ToFloat(), nan.IsNaN);
		PrintToConsoleAll("mult exp: 0.33333333333 10.0 NaN IsNaN: 1");
	}
	
	// public native void DivideRef(Double right);
	// public static native Double Divide(Double left, Double right);
	{
		Double five = Double.FromInt(5);
		PrintToConsoleAll("mult: %f %f %f", five.ToFloat(), five.DivideRef(five).ToFloat(), Double.Divide(five, five).ToFloat());
	}
	
	// public native void PowRef(Double right);
	// public static native Double Pow(Double left, Double right);
	{
		Double five = Double.FromInt(5);
		PrintToConsoleAll("mult: %f %f %f", five.ToFloat(), five.PowRef(five).ToFloat(), Double.Pow(five, five).ToFloat());
	}
	
	// public native void SquareRootRef();
	// public static native Double SquareRoot(Double right);
	{
		Double ten = Double.FromInt(10)
		Double five = Double.Add(ten, ten);

		PrintToConsoleAll("mult: %f %f %f", five.ToFloat(), five.SquareRootRef().ToFloat(), Double.SquareRoot(five).ToFloat());
	}

}