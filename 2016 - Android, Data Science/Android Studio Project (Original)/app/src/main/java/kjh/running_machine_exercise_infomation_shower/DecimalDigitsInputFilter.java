package kjh.running_machine_exercise_infomation_shower;

import android.text.InputFilter;
import android.text.Spanned;

/**
 * Created by com on 2016-02-18.
 * 인터넷에서 긁어온 코드입니다.
 * 출처: http://stackoverflow.com/questions/17423483/how-to-limit-edittext-length-to-7-integers-and-2-decimal-places
 *
 * 공부할 자료
 * https://ko.wikipedia.org/wiki/%EC%A0%95%EA%B7%9C_%ED%91%9C%ED%98%84%EC%8B%9D
 */
public class DecimalDigitsInputFilter implements InputFilter {

	private static final int
	maxDigitsBeforeDecimalPoint = 2,
	maxDigitsAfterDecimalPoint = 1;

	// ?는 바로 앞에 글자가 하나 있거나 없으면 된다는 뜻
	// 즉, 숫자가 있을 수도 있고, 콤마가 있을 수도 있고,
	// 없을 수도 있음.
	// 단 점 앞에 수는 최대 2개,
	// 점 뒤에 수는 최대 하나임.
	private static final String
	regexForBeforeDot = "([0-9]{1," + (maxDigitsBeforeDecimalPoint) + "})?",
	regexForAfterDot = "(\\.[0-9]{0," + (maxDigitsAfterDecimalPoint) + "})?",
	regex = regexForBeforeDot + regexForAfterDot;


	@Override
	public CharSequence filter
	(CharSequence source, int start, int end,
	 Spanned dest, int dstart, int dend)
	{
		StringBuilder builder = new StringBuilder(dest);

		CharSequence subSequence = source.subSequence(start, end);
		String subString = subSequence.toString();

		builder.replace(dstart, dend, subString);
		if (!builder.toString().matches(regex))
		{
			if(source.length()==0)
			{
				return dest.subSequence(dstart, dend);
			}
			return "";
		}
		return null;
	}

}
