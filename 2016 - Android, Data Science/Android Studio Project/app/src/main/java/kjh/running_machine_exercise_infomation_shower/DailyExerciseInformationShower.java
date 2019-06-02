package kjh.running_machine_exercise_infomation_shower;

import android.view.View;
import android.widget.LinearLayout;
import android.widget.ScrollView;
import android.widget.TextView;

import kjh.running_machine_exercise_infomation_shower.database.*;

/**
 * Created by com on 2016-02-20.
 */
public class DailyExerciseInformationShower
{
	private static final int FONT_SIZE = 18;
	private MainActivity activity;
	private ScrollView scroll_view;
	private LinearLayout scroll_view_content;
	private DB_Helper db_helper;
	private int spinner_value;


	public DailyExerciseInformationShower(MainActivity activity, View scroll_view)
	{
		this.activity = activity;
		this.scroll_view = (ScrollView) scroll_view;
		db_helper = new DB_Helper(activity);
	}


	/* 아래 변수는 tab2 와 tab3 에서 독립적으로 사용된다. 다른 객체에 속한 변수이다.*/
	private String prev_date = null;
	public void show_one_day(int year, int month, int day)
	{
		prev_date = null;
		scroll_view.removeView(scroll_view_content);
		scroll_view_content = init_content();
		add_contents_by_date(year, month, day);
	}


	public void update_by_spinner_value()
	{
		prev_date = null;
		scroll_view.removeView(scroll_view_content);
		scroll_view_content = init_content();
		add_contents_by_spinner_value();
	}

	/** contents 를 담을 공간을 만든다. */
	private LinearLayout init_content()
	{
		LinearLayout new_layout;
		new_layout = new LinearLayout(activity);
		new_layout.setOrientation(LinearLayout.VERTICAL);
		scroll_view.addView(new_layout);

		return new_layout;
	}


	private void add_contents_by_spinner_value()
	{
		DB_Values db_values;
		db_values = db_helper.getValuesBySpinnerValue(spinner_value);
		show_all_values(db_values);
	}

	private void add_contents_by_date(int year, int month, int day)
	{
		DB_Values db_values;
		db_values = db_helper.getValuesByDate(year, month, day);
		show_all_values(db_values);
	}


	private void show_all_values(DB_Values db_values)
	{
		while (db_values != null )
		{
			show_values(db_values);
			db_values = db_values.get_previous_value();
		}
	}

	private void show_values(DB_Values values)
	{
		String date, str_value;
		date = values.date;
		if ( !date.equals(prev_date))
		{
			show_daily_values(date);
			prev_date = date;
		}
		str_value = values.toString();
		show_text(str_value);
	}


	private void show_daily_values(String date)
	{
		DB_DailyValues values;
		String str_values;

		values = db_helper.getDailyValues(date);
		str_values = values.toString();
		show_text(str_values);
	}


	private void show_text(String string)
	{
		TextView text;
		text = new TextView(activity);
		text.setText(string);
		text.setTextSize(FONT_SIZE);
		scroll_view_content.addView(text);
	}

	public void set_spinner_value(int spinner_value)
	{
		this.spinner_value = spinner_value;
	}
}


