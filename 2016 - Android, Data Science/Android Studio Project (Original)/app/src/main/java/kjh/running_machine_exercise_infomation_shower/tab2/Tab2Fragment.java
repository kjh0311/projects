package kjh.running_machine_exercise_infomation_shower.tab2;

import android.support.v4.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import kjh.running_machine_exercise_infomation_shower.DailyExerciseInformationShower;
import kjh.running_machine_exercise_infomation_shower.MainActivity;
import kjh.running_machine_exercise_infomation_shower.R;
import kjh.running_machine_exercise_infomation_shower.tab2.action_setter.SpinnerViewActionSetter;
import kjh.running_machine_exercise_infomation_shower.tab2.action_setter.TestViewActionSetter;

/**
 * Created by yun on 2016-02-18.
 */
public class Tab2Fragment extends Fragment
{
	SpinnerViewActionSetter spinner_view_action_setter;
	TestViewActionSetter test_view_action_setter;
	DailyExerciseInformationShower exercise_information_shower;

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
							 Bundle savedInstanceState)
	{
		MainActivity activity;
		View tab2, spinner_view, test_view, scroll_view;

		activity = (MainActivity) getActivity();
		tab2 = inflater.inflate(R.layout.tab2, container, false);
		spinner_view = tab2.findViewById(R.id.spinner_view);
		test_view = tab2.findViewById(R.id.test_view);
		scroll_view = tab2.findViewById(R.id.scroll_view);

		spinner_view_action_setter = new SpinnerViewActionSetter(activity, spinner_view);
		test_view_action_setter = new TestViewActionSetter(activity, test_view);
		exercise_information_shower = new DailyExerciseInformationShower(activity, scroll_view);
		set_actions();
		return tab2;
	}


    void set_actions()
	{
		spinner_view_action_setter.set_actions(exercise_information_shower, test_view_action_setter);
		test_view_action_setter.set_actions(exercise_information_shower);
		/* 각 객체간에 서로 상호작용을 하게 한다.
		   스크롤뷰에 내용 보여주기는,
		   spinner_view_action_setter 가 스크롤뷰에 몇개의 내용을 보여줄지를 가지고 있으므로,
		   spinner_view_action_setter 가 scroll_view_contents_shower 를 매개변수로 받아서,
		   실행하도록 한다.
		 */
	}


	public void update()
	{
		exercise_information_shower.update_by_spinner_value();
	}
}
