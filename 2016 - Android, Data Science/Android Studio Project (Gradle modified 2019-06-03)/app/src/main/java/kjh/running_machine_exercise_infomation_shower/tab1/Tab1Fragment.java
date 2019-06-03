package kjh.running_machine_exercise_infomation_shower.tab1;

import android.support.v4.app.Fragment;
import android.os.Bundle;
import android.text.InputFilter;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

import kjh.running_machine_exercise_infomation_shower.DecimalDigitsInputFilter;
import kjh.running_machine_exercise_infomation_shower.MainActivity;
import kjh.running_machine_exercise_infomation_shower.R;

/**
 * Created by com on 2016-02-24.
 */
public class Tab1Fragment extends Fragment
{
	public void update()
	{

	}

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
							 Bundle savedInstanceState)
	{
		View tab1;
		tab1 = inflater.inflate(R.layout.tab1, container, false);
		set_actions(tab1);
		return tab1;
	}


	void set_actions(View tab1) {
		View current, start;

		current = tab1.findViewById(R.id.current_value);
		start = tab1.findViewById(R.id.start_value);

		set_view_actions(current, CurrentOrStart.CURRENT);
		set_view_actions(start, CurrentOrStart.START);
	}


	private void set_view_actions(View view, CurrentOrStart current_or_start) {
		View grad_and_speed, grad, speed;

		grad_and_speed = view.findViewById(R.id.grad_and_speed);

		grad = grad_and_speed.findViewById(R.id.grad);
		speed = grad_and_speed.findViewById(R.id.speed);

		set_control_actions(current_or_start, GradOrSpeed.GRAD, grad);
		// set_control_actions 를 연달아 쓰면 에러가 난다.
		set_control_actions(current_or_start, GradOrSpeed.SPEED, speed);
	}


	private void set_control_actions
			(CurrentOrStart current_or_start, GradOrSpeed grad_or_speed , View control_view)
	{
		MainActivity activity;
		ControlActionSetter setter;

		activity = (MainActivity) getActivity();
		setter = new ControlActionSetter(activity, current_or_start, grad_or_speed, control_view);
		setter.set_actions();
	}
}

enum CurrentOrStart {
	CURRENT, START;
}

enum GradOrSpeed {
	GRAD, SPEED;
}


class ControlActionSetter {
	MainActivity content;
	CurrentOrStart current_or_start;
	GradOrSpeed grad_or_speed;
	Tab1DBHelper tab1DBHelper;
	EditText edit;
	ImageButton up, double_up, down, double_down;
	Button set_button;

	ControlActionSetter(MainActivity content, CurrentOrStart current_or_start, GradOrSpeed grad_or_speed
			, View control_view)
	{
		View control_set, two_up_buttons, two_down_buttons;
		control_set = control_view.findViewById(R.id.control_set);
		//control_set.setVisibility(View.INVISIBLE);
		two_up_buttons = control_set.findViewById(R.id.two_up_buttons);
		two_down_buttons = control_set.findViewById(R.id.two_down_buttons);

		this.content = content;
		this.current_or_start = current_or_start;
		this.grad_or_speed = grad_or_speed;
		tab1DBHelper = new Tab1DBHelper(content, current_or_start, grad_or_speed);

		edit = (EditText) control_set.findViewById(R.id.edit_value);
		up = (ImageButton) two_up_buttons.findViewById(R.id.up);
		double_up = (ImageButton) two_up_buttons.findViewById(R.id.double_up);
		down = (ImageButton) two_down_buttons.findViewById(R.id.down);
		double_down = (ImageButton) two_down_buttons.findViewById(R.id.double_down);

		set_button = (Button) control_view.findViewById(R.id.set_button);
	}


	public void set_actions() {
		fill_edit_text();
		limit_edit_text_digit();
		set_button_actions();
	}

	private void fill_edit_text()
	{
		double value;
		value = tab1DBHelper.read_value();
		edit.setText(String.format("%s", value));
	}


	private void limit_edit_text_digit() {
		edit.setFilters
				(new InputFilter[]
								{new DecimalDigitsInputFilter()}
				);
	}



	private void set_button_actions() {

		ButtonsClickListener l = new ButtonsClickListener();
		// 가장 쉬운 것부터 해봄
		set_button.setOnClickListener(l);
		up.setOnClickListener(l);
		double_up.setOnClickListener(l);
		down.setOnClickListener(l);
		double_down.setOnClickListener(l);
	}


	// 버튼을 누르면 값은 변해야함
	class ButtonsClickListener implements View.OnClickListener {
		@Override
		public void onClick(View view) {

			int view_id;
			String str_value;

			view_id = view.getId();
			str_value = edit.getText().toString();
			str_value = change_value(view_id, str_value);
			edit.setText(str_value);
			show_toast(str_value);
		}
	}


	private String change_value(int view_id, String str_value) {
		Double number_value;
		number_value = Double.parseDouble(str_value);
		switch (view_id) {
			case R.id.up:
				number_value = up(number_value, 0.1);
				break;
			case R.id.double_up:
				number_value = up(number_value, 0.5);
				break;
			case R.id.down:
				number_value = down(number_value, 0.1);
				break;
			case R.id.double_down:
				number_value = down(number_value, 0.5);
				break;
			// 설정 버튼을 눌렀을 때 발생
			default:
				number_value = saturate(number_value);
				break;
		}
		str_value = String.format("%2.1f", number_value);
		update_db(number_value);

		return str_value;
	}


	private void update_db(double number_value)
	{
		tab1DBHelper.write_value(number_value);
	}


	private double saturate(double number_value) {
		if (number_value > 20) {
			number_value = 20.0;
		}
		return number_value;
	}


	private double up(Double number_value, double factor) {
		number_value += factor;
		number_value = saturate(number_value);
		return number_value;
	}


	private double down(Double number_value, double factor) {
		number_value -= factor;
		if (number_value < 0) {
			number_value = 0.0;
		}
		return number_value;
	}


	private static Toast toast;
	private void show_toast(String str) {
		String front="", rear="";
		switch ( current_or_start ) {
			case CURRENT:
				front += "현재값\n";
				break;
			case START:
				front += "시작값\n";
				break;
			default: break;
		}

		switch ( grad_or_speed ) {
			case GRAD:
				front += "경사: ";
				rear += "%";
				break;
			case SPEED:
				front += "속도: ";
				rear += "km/h";
				break;
			default:
				front += "";
				rear += "";
		}
		str = front + str + rear + "로 설정됨";
		// 바로바로 변하게 하려고 cancel 을 함
		if (toast != null) {
			toast.cancel();
		}
		toast = Toast.makeText(content, str, Toast.LENGTH_SHORT);
		TextView v = (TextView)toast.getView().findViewById(android.R.id.message);
		if( v != null) v.setGravity(Gravity.CENTER);
		toast.show();
	}
}