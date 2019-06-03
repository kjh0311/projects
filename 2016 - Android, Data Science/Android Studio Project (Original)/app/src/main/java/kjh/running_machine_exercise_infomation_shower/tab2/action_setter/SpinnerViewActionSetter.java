package kjh.running_machine_exercise_infomation_shower.tab2.action_setter;

import android.view.View;
import android.widget.AdapterView;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.LinearLayout;
import android.widget.Spinner;

import kjh.running_machine_exercise_infomation_shower.DailyExerciseInformationShower;
import kjh.running_machine_exercise_infomation_shower.MainActivity;
import kjh.running_machine_exercise_infomation_shower.R;


/**
 * Created by com on 2016-02-22.
 */

public class SpinnerViewActionSetter
{
	/*
	DailyExerciseInformationShower 에서도 참조할 값이므로,
	private 를 붙히지 않았다.
	 */
	public static final int
			ONE_DAY = 0, THREE_DAYS = 1, FIVE_DAYS = 2,
			ONE_WEEK = 3, TWO_WEEKS = 4, ONE_MONTH = 5,
			ONE_YEAR = 6, ALL = 7,
			DEFAULT = ONE_WEEK;
	private Spinner spinner_number_of_days;
	private CheckBox check_hide_test_view;


	public SpinnerViewActionSetter(MainActivity tab2, View spinner_view)
	{
		spinner_number_of_days = (Spinner) spinner_view.findViewById(R.id.spinner_days);
		check_hide_test_view = (CheckBox) spinner_view.findViewById(R.id.check_hide_test_view);
		spinner_number_of_days.setSelection(DEFAULT);
	}


	public void set_actions(DailyExerciseInformationShower exercise_information_shower, TestViewActionSetter test_view_action_setter)
	{
		set_spinner_action(exercise_information_shower);
		set_check_action(test_view_action_setter);
	}


	private void set_spinner_action(final DailyExerciseInformationShower exercise_information_shower)
	{
		spinner_number_of_days.setOnItemSelectedListener
				(new AdapterView.OnItemSelectedListener()
		{
			@Override
			public void onItemSelected(AdapterView<?> parent, View view, int pos, long id)
			{
				exercise_information_shower.set_spinner_value(pos);
				exercise_information_shower.update_by_spinner_value();
			}

			@Override
			public void onNothingSelected(AdapterView<?> adapterView)
			{

			}
		});
	}


	private void set_check_action(final TestViewActionSetter test_view_action_setter)
	{
		check_hide_test_view.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
			@Override
			public void onCheckedChanged(CompoundButton compoundButton, boolean checked) {
				LinearLayout.LayoutParams params;
				LinearLayout test_view = test_view_action_setter.getTestView();
				if (checked) {
					params = new LinearLayout.LayoutParams
							(LinearLayout.LayoutParams.MATCH_PARENT, 0);
					test_view.setLayoutParams(params);
				} else {
					params = new LinearLayout.LayoutParams
							(LinearLayout.LayoutParams.MATCH_PARENT,
									LinearLayout.LayoutParams.WRAP_CONTENT);
					test_view.setLayoutParams(params);
				}
			}
		});
	}
}
