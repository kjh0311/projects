package kjh.running_machine_exercise_infomation_shower.database;

import android.database.Cursor;

public class DB_Values
{
	private DB_Values prev_values;
	public String date,
			start, end, elapsed,
			kcal, km, grad, speed;
	private static final int
			DATE = 0, START_TIME = 1, END_TIME = 2, ELAPSED_TIME = 3,
			KCAL = 4, KM = 5, GRAD = 6, SPEED = 7;
	public DB_Values(Cursor cursor, DB_Values values)
	{
		prev_values = values;
		date = cursor.getString(DATE);
		start = cursor.getString(START_TIME);
		end = cursor.getString(END_TIME);
		elapsed = cursor.getString(ELAPSED_TIME);
		kcal = cursor.getString(KCAL);
		km = cursor.getString(KM);
		grad = cursor.getString(GRAD);
		speed = cursor.getString(SPEED);
	}

	public DB_Values get_previous_value() {
		return prev_values;
	}


	public String toString()
	{
		class Converted {
			String date,
					exercise_time, elapsed_time,
					kcal, km, grad, speed;
		}
		DB_ValueConverter converter;
		Converted converted;
		StringBuilder values;

		converter = new DB_ValueConverter();
		converted = new Converted();
		values = new StringBuilder();

		converted.exercise_time = converter.convert_exercise_time(start, end);
		converted.elapsed_time = converter.convert_elapsed_time(elapsed);
		converted.kcal = converter.convert_kcal(kcal);
		converted.km = converter.convert_km(km);
		converted.grad = converter.convert_grad(grad);
		converted.speed = converter.convert_speed(speed);


		values.append(converted.exercise_time);
		values.append("\n");
		values.append(converted.elapsed_time);
		values.append("\n\n");
		values.append(converted.kcal);
		values.append("\t\t");
		values.append(converted.km);
		values.append("\n");
		values.append(converted.grad);
		values.append("\t\t");
		values.append(converted.speed);
		values.append("\n");


		return values.toString();
	}

}