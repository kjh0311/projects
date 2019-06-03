package kjh.running_machine_exercise_infomation_shower;

import android.support.v4.app.FragmentTransaction;
import android.widget.Toast;

import java.nio.charset.Charset;

import kjh.running_machine_exercise_infomation_shower.bluetooth_client_fragment.BluetoothClientFragment;
import kjh.running_machine_exercise_infomation_shower.bluetooth_client_fragment.BluetoothMessageReceiver;
import kjh.running_machine_exercise_infomation_shower.database.DB_Helper;

/**
 * Created by kimjin on 2016-03-24.
 *
 * 이 클래스는,
 * 실행하자마자
 * BluetoothClientFragment 에 있는 방법대로
 * 특정 주소의 블루투스 디바이스로 접속해서,
 * 그 디바이스로 부터 정보를 얻어온다.
 *
 *
 * 이 동작을 하기 위해서,
 * 이 클래스는 BluetoothMessageReceiver 클래스를
 * implements 하고,
 * BluetoothClientFragment 클래스를 사용하고,
 * DB_Helper 클래스를 사용한다.
 * 그리고 그 결과를 반영하기 위해,
 * MainActivity 에 update 메서드를 불러,
 * 그 클래스에서 세부적인 update 를 한다.
 *
 */
public class BluetoothClient implements BluetoothMessageReceiver
{
    private MainActivity main_activity;
    private BluetoothClientFragment fragment;
    boolean wait_to_connect;
    public BluetoothClient(MainActivity activity)
    {
        FragmentTransaction transaction;
        main_activity = activity;
        fragment = new BluetoothClientFragment();
        wait_to_connect = false;
        transaction = activity.getSupportFragmentManager().beginTransaction();
        transaction.replace(R.id.activity_main, fragment);
        transaction.commit();
    }


    public void connect()
    {
	    fragment.set_auto_connect_receiver(this);
	    // fragment 에서 onCreate 보다 이것이 먼저 실행될 수 없으므로,
	    // 위의 방법을 쓴다.
		//fragment.connect_and_set_receiver(this);
    }


    /*
    아래 메서드에서 메세지 받았을 때의 기능을 한다.
    제일 먼저는 테스트를 위해서 Toast를 부르고,
    그 다음에 데이터베이스 사용과 main_activity를 업데이트 하는 일을 한다.
     */
    @Override
    public void use_received_message(String message)
    {

	    DB_Helper db_helper;
	    StringBuilder insert_parameter;



	    db_helper = new DB_Helper(main_activity);
	    insert_parameter = new StringBuilder(message);
	    db_helper.insert(insert_parameter);


	    main_activity.update();


		//Toast.makeText(main_activity, message, Toast.LENGTH_LONG).show();
    }
}
