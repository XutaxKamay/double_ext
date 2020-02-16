#if defined _double_included
 #endinput
#endif
#define _double_included

methodmap Double < Handle
{
    propery bool IsNaN
    {
        public native get();
    }

	public native Double();

	public static native Double FromString(char[] value);
	public static native Double FromInt(int value);
	public static native Double FromFloat(float value);

	public native void ToString(char[] buffer, int maxlen);
	public native int ToInt();
	public native float ToFloat();

	public static native bool GreaterThan(Double left, Double right);
	public static native bool LessThan(Double left, Double right);
	public static native bool EqualTo(Double left, Double right);

	public native Double Clone(Double value);

	public native void AbsoluteRef();
	public static native Double Absolute(Double value);

	public native void ModuloRef(Double denominator);
	public static native Double Modulo(Double number, Double denominator);

	public native void AddRef(Double right);
	public static native Double Add(Double left, Double right);

	public native void SubstractRef(Double right);
	public static native Double Substract(Double left, Double right);
	
	public native void MultiplyRef(Double right);
	public static native Double Multiply(Double left, Double right);

	public native void DivideRef(Double right);
	public static native Double Divide(Double left, Double right);

	public native void PowRef(Double right);
	public static native Double Pow(Double left, Double right);

	public native void SquareRootRef();
	public static native Double SquareRoot(Double right);

	public native void AtanRef();
	public static native Double Atan(Double right);
    
	public native void Atan2Ref(Double right);
	public static native Double Atan2(Double left, Double right);

	public native void SineRef();
	public static native Double Sine(Double angle);

	public native void ArcSineRef();
	public static native Double ArcSine(Double angle);

	public native void TangentRef();
	public static native Double Tangent(Double angle);

	public native void CosineRef();
	public static native Double Cosine(Double angle);

	public native void ArcCosineRef();
	public static native Double ArcCosine(Double angle);
}
