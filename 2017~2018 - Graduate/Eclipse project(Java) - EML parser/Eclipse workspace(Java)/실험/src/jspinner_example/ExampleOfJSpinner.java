package jspinner_example;

import java.util.Calendar;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JSpinner;
import javax.swing.SpinnerDateModel;
import javax.swing.text.DateFormatter;

public class ExampleOfJSpinner
{	
	private static final String
	// 대문자와 소문자는 의미에 차이가 있음.
	//date_and_time_format = "yyyy-MM-dd HH:mm:ss";
	// 아래 두 형태 채택
	//date_and_time_format = "a hh:mm";
	date_and_time_format = "yyyy년 MM월 dd일";
	/*
	 * 사용법 정리(대소문자 구분 있음)
	 * yyyy: 연, yy: 연(두 자리)
	 * MM: 월, dd: 일
	 * HH: 24시간 기준의 시간
	 * hh: 12시간 기준의 시간
	 * a: 오전/오후
	 * mm: 분
	 * ss: 초
	 * 
	 * 이것들 이외에도, 
	 * 일년중에 날 수(DDD),
	 * 월 중에 주(F)
	 * 요일(E)
	 * 등등이 있음
	 */
	
	
	
	
	
	
    public static void main(String[] args)
    {
    	new ExampleOfJSpinner();
    }	
	
	
	private ExampleOfJSpinner()
	{
		Calendar calendar = Calendar.getInstance();
		//calendar.set(Calendar.HOUR_OF_DAY, 24); // 24 == 12 PM == 00:00:00
		//calendar.set(Calendar.MINUTE, 0);
		//calendar.set(Calendar.SECOND, 0);

		SpinnerDateModel model = new SpinnerDateModel();
		//model.setValue(calendar.getTime());
		model.setValue(calendar.getTime()); // 오늘을 가져옴

		JSpinner spinner = new JSpinner(model);

		JSpinner.DateEditor editor = new JSpinner.DateEditor(spinner, date_and_time_format);
		DateFormatter formatter = (DateFormatter)editor.getTextField().getFormatter();
		formatter.setAllowsInvalid(false); // this makes what you want
		formatter.setOverwriteMode(true);

		spinner.setEditor(editor);

		JPanel content = new JPanel();
		content.add(spinner);

		JFrame frame = new JFrame("ExampleOfJSpinner");
		frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		frame.getContentPane().add(content);
		frame.pack();
		frame.setLocationRelativeTo(null);
		frame.setVisible(true);
	}	
}
