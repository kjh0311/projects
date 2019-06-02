package kjh.running_machine_exercise_infomation_shower.tab2.action_setter;

import android.content.res.Resources;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.Spinner;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;
import java.util.StringTokenizer;

import kjh.running_machine_exercise_infomation_shower.DailyExerciseInformationShower;
import kjh.running_machine_exercise_infomation_shower.MainActivity;
import kjh.running_machine_exercise_infomation_shower.R;
import kjh.running_machine_exercise_infomation_shower.database.*;

/**
 * Created by com on 2016-02-19.
 */
public class TestViewActionSetter
{
	private MainActivity main_activity;
	private LinearLayout test_view;
	private EditText
			edit_month, edit_day,
			edit_start_hour, edit_start_minute,
			edit_end_hour, edit_end_minute,
			edit_kcal, edit_km, edit_grad, edit_speed;
	private Spinner spinner_start_ampm, spinner_end_ampm;
	private Button save_button;


	public TestViewActionSetter
			(MainActivity main_activity, View test_view)
	{
		View test_view_day, test_view_start_time_and_save_button,
				test_view_end_time, test_view_exercise_info;
		View test_view_start_time;

		this.main_activity = main_activity;
		this.test_view = (LinearLayout) test_view;


		test_view_day = test_view.findViewById(R.id.test_view_day);
		test_view_start_time_and_save_button
				= test_view.findViewById(R.id.test_view_start_time_and_save_button);
		test_view_end_time = test_view.findViewById(R.id.test_view_end_time);
		test_view_exercise_info = test_view.findViewById(R.id.test_view_exercise_info);

		test_view_start_time
				= test_view_start_time_and_save_button.findViewById(R.id.test_view_time);
		test_view_end_time
				= test_view_end_time.findViewById(R.id.test_view_time);



		edit_month = (EditText) test_view_day.findViewById(R.id.edit_month);
		edit_day = (EditText) test_view_day.findViewById(R.id.edit_day);

		
		spinner_start_ampm = (Spinner) test_view_start_time.findViewById(R.id.spinner_ampm);
		edit_start_hour = (EditText) test_view_start_time.findViewById(R.id.edit_hour);
		edit_start_minute = (EditText) test_view_start_time.findViewById(R.id.edit_minute);
		
		spinner_end_ampm = (Spinner) test_view_end_time.findViewById(R.id.spinner_ampm);
		edit_end_hour = (EditText) test_view_end_time.findViewById(R.id.edit_hour);
		edit_end_minute = (EditText) test_view_end_time.findViewById(R.id.edit_minute);

		
		edit_kcal = (EditText) test_view_exercise_info.findViewById(R.id.edit_kcal);
		edit_km = (EditText) test_view_exercise_info.findViewById(R.id.edit_km);
		edit_grad = (EditText) test_view_exercise_info.findViewById(R.id.edit_grad);
		edit_speed = (EditText) test_view_exercise_info.findViewById(R.id.edit_speed);

		save_button	= (Button) test_view_start_time_and_save_button.findViewById(R.id.save_button);

		DateStrings strings;
		strings = getDateStrings();

		edit_month.setText(strings.month);
		edit_day.setText(strings.day);
		edit_start_hour.setText(strings.hour);
		edit_end_hour.setText(strings.hour);
		edit_start_minute.setText(strings.minute);
		edit_end_minute.setText(strings.minute);
	}


	class DateStrings
	{
		String month, day, hour, minute;
	}


	private DateStrings getDateStrings() {
		Date date;
		SimpleDateFormat formatter;
		String string;
		StringTokenizer tokenizer;
		DateStrings strings;



		date = new Date();
		formatter = new SimpleDateFormat ( "MM:dd:HH:mm", Locale.KOREA );
		string = formatter.format ( date );
		tokenizer = new StringTokenizer(string, ":");
		strings = new DateStrings();

		strings.month = tokenizer.nextToken();
		strings.day = tokenizer.nextToken();
		strings.hour = tokenizer.nextToken();
		strings.minute = tokenizer.nextToken();


		return strings;
	}


	public void set_actions(final DailyExerciseInformationShower exercise_information_shower)
	{
		save_button.setOnClickListener
		(new View.OnClickListener()
		{
			@Override
			public void onClick(View view)
			{
				save_all();
				exercise_information_shower.update_by_spinner_value();
			}
		});
	}


	private void save_all()
	{
		DB_Helper db_helper;
		StringBuilder insert_parameter;
		SQLiteInsertParameterMaker insertParameterMaker;
		db_helper = new DB_Helper(main_activity);
		insertParameterMaker = new SQLiteInsertParameterMaker();


		insert_parameter = insertParameterMaker.makeDatabaseInsertParameter();
		db_helper.insert(insert_parameter);
	}

	public LinearLayout getTestView() {
		return test_view;
	}


	// 데이터베이스에 넣을 String 을 만들어낸다.
	// 주어진 값을 가지고 계산도 한다.
	class SQLiteInsertParameterMaker
	{
		String
		month, day,
		kcal, km, grad, speed;

		class Time
		{
			String ampm, hour, minute;
		}

		// 계산되어서 생성될 값
		Time start, end, elapsed;
		SQLiteInsertParameterMaker()
		{
			start = new Time();
			end = new Time();
			elapsed = new Time();

			extract_all_strings();
			// get_elapsed_time();
		}


		private void extract_all_strings()
		{
			month = edit_month.getText().toString();
			day = edit_day.getText().toString();

			start.ampm = spinner_start_ampm.getSelectedItem().toString();
			start.hour = edit_start_hour.getText().toString();
			start.minute = edit_start_minute.getText().toString();

			end.ampm = spinner_end_ampm.getSelectedItem().toString();
			end.hour = edit_end_hour.getText().toString();
			end.minute = edit_end_minute.getText().toString();

			kcal = edit_kcal.getText().toString();
			km = edit_km.getText().toString();
			grad = edit_grad.getText().toString();
			speed = edit_speed.getText().toString();
		}

		// 밖에서 불릴 메소드
		StringBuilder makeDatabaseInsertParameter()
		{
			String date, start_time, end_time;
			StringBuilder insert_parameter;


			date = get_date();
			start_time = get_time(start);
			end_time = get_time(end);
			//elapsed_time = get_time(elapsed);

			// 덧붙히기를 많이 할 경우,
			// String 대신에 StringBuilder 를 쓰는 것이 더 빠르고,
			// 메모리를 절약해서 바람직하다.
			insert_parameter = new StringBuilder(date);
			add_string(insert_parameter, start_time);
			add_string(insert_parameter, end_time);
			//add_string(insert_parameter, elapsed_time);


			add_string(insert_parameter, kcal);
			add_string(insert_parameter, km);
			add_string(insert_parameter, grad);
			add_string(insert_parameter, speed);

			return insert_parameter;
		}

		private void add_string(StringBuilder insert_parameter, String string) {
			insert_parameter.append(", ");
			insert_parameter.append(string);
		}


		private String get_date()
		{
			String date = "";

			month = fix_to_2digits(month);
			day = fix_to_2digits(day);

			date += "'";
			date += "2016-" + month + "-" + day;
			date += "'";
			return date;
		}


		private String get_time(Time time)
		{
			String ampm, hour, minute;
			Resources res;
			String ampm_array[], PM;
			int int_hour;
			String destination = "";


			ampm = time.ampm;
			hour = time.hour;
			minute = time.minute;


			res = main_activity.getResources();
			ampm_array = res.getStringArray(R.array.ampm);
			PM = ampm_array[1];

			int_hour = Integer.parseInt(hour);
			if (ampm.equals(PM))
				int_hour += 12;
			hour = Integer.toString(int_hour);
			hour = fix_to_2digits(hour);
			minute = fix_to_2digits(minute);

			destination += "'";
			destination += hour + ":" + minute;
			destination += "'";
			return destination;
		}


		private String fix_to_2digits(String str_digit) {
			while (str_digit.length() < 2) {
				str_digit = "0"+str_digit;
			}
			return str_digit;
		}
	}
}
