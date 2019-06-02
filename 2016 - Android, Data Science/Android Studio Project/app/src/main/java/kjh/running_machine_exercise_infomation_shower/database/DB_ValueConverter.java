package kjh.running_machine_exercise_infomation_shower.database;

import java.util.StringTokenizer;

/**
 * Created by com on 2016-02-21.
 */
public class DB_ValueConverter
{
	public String convert_date(String date)
	{
		StringTokenizer tokenizer;
		String year, month, day;

		tokenizer = new StringTokenizer(date, "-");
		year = tokenizer.nextToken();
		month = tokenizer.nextToken();
		day = tokenizer.nextToken();


		return year+"년 "+month+"월 "+day+"일";
	}

	public String convert_total_time(String time)
	{
		return "총 " + convert_elapsed_time(time);
	}


	public String convert_total_kcal(String kcal)
	{
		return "총 " + convert_kcal(kcal);
	}


	public String convert_total_km(String km)
	{
		return "총 " + convert_km(km);
	}


	public String convert_elapsed_time(String time)
	{
		StringTokenizer tokenizer;
		String hour, minute;

		tokenizer = new StringTokenizer(time, ":");
		hour = tokenizer.nextToken();
		minute = tokenizer.nextToken();
		hour = trim_upper_zero(hour);
		minute = trim_upper_zero(minute);

		if ( hour.equals("0") )
			return "운동시간: " + minute + "분";
		else
			return "운동시간: " + hour + "시간 " + minute + "분";
	}

	private String trim_upper_zero(String two_digit) {
		int i = Integer.parseInt(two_digit);
		return Integer.toString(i);
	}


	public String convert_kcal(String kcal) {
		return "칼로리 소모: " + kcal + "kcal";
	}


	public String convert_km(String km) {
		return "이동 거리: " + km + "km";
	}


	public String convert_grad(String grad) {
		return "경사: " + grad + "%";
	}


	public String convert_speed(String speed) {
		return "속도: " + speed + "km/h";
	}


	public class Time
	{
		String ampm, hour, minute;
	}


	public String convert_exercise_time(String str_start, String str_end)
	{
		Time start, end;
		StringBuilder string_bulider;
		String string;



		start = string_to_time(str_start);
		end = string_to_time(str_end);
		string_bulider = new StringBuilder();

		string_bulider.append(start.ampm + " " + getTime(start) + " ~ ");
		if ( start.ampm.equals(end.ampm) ) {
			string_bulider.append(getTime(end));
		}
		else {
			string_bulider.append(end.ampm + " " + getTime(end));
		}


		// 한 줄 위에 구분선 표시하기
		string = string_bulider.toString();
		//byteArray = string.getBytes();
		string_bulider = new StringBuilder();
		// byteArray.length * 1 / 3
		// 대강 재보니까 글자 수의 11/19 정도 그으면 됨
		for (int i = 0; i < string.length() * 11 / 19 ; i++) {
			string_bulider.append("--  ");
		}
		string_bulider.append("--");
		string_bulider.append("\n");
		string_bulider.append(string);


		return string_bulider.toString();
	}


	private String getTime(Time time)
	{
		time.hour = trim_upper_zero(time.hour);
		time.minute = trim_upper_zero(time.minute);
		return time.hour + "시 " + time.minute + "분";
	}




	private Time string_to_time(String str_time)
	{
		Time time;
		StringTokenizer tokenizer;
		String minute;
		int int_hour;


		time = new Time();
		tokenizer = new StringTokenizer(str_time, ":");
		time.hour = tokenizer.nextToken();
		time.minute = tokenizer.nextToken();

		int_hour = Integer.parseInt(time.hour);
		if (int_hour < 12) {
			time.ampm = "오전";
		} else {
			time.ampm = "오후";
		}
		return time;
	}
}
