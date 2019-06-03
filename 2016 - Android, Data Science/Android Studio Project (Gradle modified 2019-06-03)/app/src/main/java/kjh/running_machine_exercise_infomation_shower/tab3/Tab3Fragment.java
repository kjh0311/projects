package kjh.running_machine_exercise_infomation_shower.tab3;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.CalendarView;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.LinearLayout;
import android.widget.ScrollView;
import android.widget.Toast;

import java.text.SimpleDateFormat;
import java.util.StringTokenizer;
import java.util.Timer;
import java.util.TimerTask;

import kjh.running_machine_exercise_infomation_shower.DailyExerciseInformationShower;
import kjh.running_machine_exercise_infomation_shower.MainActivity;
import kjh.running_machine_exercise_infomation_shower.R;

/**
 * Created by com on 2016-02-24.
 */
public class Tab3Fragment extends Fragment
{
	private CalendarView calendar_view;
	private ScrollView scroll_view;
	private DailyExerciseInformationShower exercise_information_shower;
	private DateChangeListener date_change_listener;

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
							 Bundle savedInstanceState)
	{
		MainActivity activity;
		View tab3;

		activity = (MainActivity) getActivity();
		tab3 = inflater.inflate(R.layout.tab3, container, false);
		calendar_view = (CalendarView) tab3.findViewById(R.id.calendar_view);
		scroll_view = (ScrollView) tab3.findViewById(R.id.scroll_view);
		exercise_information_shower = new DailyExerciseInformationShower(activity, scroll_view);
		date_change_listener = new DateChangeListener();

		set_actions(tab3);
		return tab3;
	}

	private void set_actions(View tab3)
	{
		set_check_box_actions(tab3);
		set_calendar_action(tab3);
		set_button_action(tab3);
	}


	private void set_check_box_actions(View tab3)
	{
		CheckBox check_hide_calendar;
		check_hide_calendar = (CheckBox) tab3.findViewById(R.id.check_hide_calendar);
		check_hide_calendar.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
			@Override
			public void onCheckedChanged(CompoundButton compoundButton, boolean checked) {
				if (checked) {
					hide_calendar();
				} else {
					show_calendar();
				}
			}
		});
	}


	private void set_calendar_action(View tab3)
	{
		calendar_view.setOnDateChangeListener(date_change_listener);
		show_today_exercise_information(date_change_listener, calendar_view);
	}


	DatePickerFragment newFragment;
	private void set_button_action(View tab3)
	{
		Button set_button;

		newFragment = new DatePickerFragment();
		set_button = (Button) tab3.findViewById(R.id.set_button);
		set_button.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View view) {
				show_date_picker();
			}
		});
	}

	private void show_date_picker()
	{
		// set_calendar_view 가 먼저 불려야함.
		newFragment.set_calendar_view(calendar_view);
		newFragment.show(getActivity().getSupportFragmentManager(), "datePicker");
	}


	private void show_today_exercise_information(DateChangeListener listener, CalendarView calendar_view)
	{
		long date;
		SimpleDateFormat formatter;
		String formatted_date;
		StringTokenizer tokenizer;
		int year, month, day;

		date = calendar_view.getDate();
		formatter = new SimpleDateFormat("yyyy-MM-dd");
		formatted_date = formatter.format(date);
		tokenizer = new StringTokenizer(formatted_date, "-");
		year = Integer.parseInt(tokenizer.nextToken());
		month = Integer.parseInt(tokenizer.nextToken());
		day = Integer.parseInt(tokenizer.nextToken());

		listener.onSelectedDayChange(calendar_view, year, month - 1, day);
	}




	class DateChangeListener implements CalendarView.OnDateChangeListener
	{
		int year, month, day;
		@Override
		public void onSelectedDayChange(CalendarView calendarView, int year, int month_index, int day)
		{
			this.year = year;
			this.month = month_index + 1;
			this.day = day;
			update();
		}		
		void update()
		{
			exercise_information_shower.show_one_day(year, month, day);
			//Toast.makeText(getActivity(), year+"-"+month+"-"+day, Toast.LENGTH_LONG).show();
		}		
	}
	
	
	public void update()
	{
		if (date_change_listener != null)
		{
			date_change_listener.update();
		}
	}


	private static final int
	animation_speed = 800, timer_interval = 50,
	max_weight = 100, min_weight = 20,
	factor = animation_speed/ timer_interval,
	timer_duration = timer_interval * max_weight /factor;
	private static final int
			HIDE = 0, SHOW = 1;


	AnimationShowAndHideTimerTask hide_task, show_task;
	private void hide_calendar()
	{
		Timer timer;
		timer = new Timer();
		if ( show_task != null )
			show_task.cancel();
		hide_task = new AnimationShowAndHideTimerTask(HIDE);
		timer.schedule(hide_task, timer_duration, timer_interval);
	}


	private void show_calendar()
	{
		Timer timer;
		timer = new Timer();
		if ( hide_task != null )
			hide_task.cancel();
		show_task = new AnimationShowAndHideTimerTask(SHOW);
		timer.schedule(show_task, timer_duration, timer_interval);
	}


	// 아래의 것이 지역변수이면 이상하게도 안 된다.
	private int weight = max_weight;
	class AnimationShowAndHideTimerTask extends TimerTask
	{
		private int hide_and_show;

		AnimationShowAndHideTimerTask(int hide_and_show)
		{
			this.hide_and_show = hide_and_show;
		}

		@Override
		public void run()
		{
			if (hide_and_show == HIDE)
			{
				hide();
			}
			else
			{
				show();
			}
		}

		private void hide()
		{
			weight -= factor;
			if (weight <= min_weight)
			{
				weight = min_weight;
				cancel();
			}
			set_calendar_view_weight(weight);
		}

		private void show()
		{
			weight += factor;
			if (weight >= max_weight)
			{
				weight = max_weight;
				cancel();
			}
			set_calendar_view_weight(weight);
		}

		private void set_calendar_view_weight(final int weight)
		{
			final LinearLayout.LayoutParams params;
			params = new LinearLayout.LayoutParams
					(LinearLayout.LayoutParams.MATCH_PARENT, 0, weight);
			calendar_view.post(new Runnable() {
				@Override
				public void run() {
					calendar_view.setLayoutParams(params);
					calendar_view.invalidate();
					if ( weight <= min_weight )
					{
						calendar_view.setVisibility(View.GONE);
					}
					else
					{
						calendar_view.setVisibility(View.VISIBLE);
					}
				}
			});
		}
	}

}