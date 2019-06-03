package kjh.running_machine_exercise_infomation_shower.bluetooth_client_fragment;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.widget.Toast;

import kjh.running_machine_exercise_infomation_shower.R;

/**
 * Created by kimjin on 2016-03-21.
 */
public class BluetoothClientFragment extends Fragment
{
    private static final String DESTINATION_ADDRESS
            = "00:1A:7D:DA:71:13";
    private static final int REQUEST_CONNECT_DEVICE_INSECURE = 2;
    private static final int REQUEST_ENABLE_BT = 3;


	private boolean auto_connect = false;
    private BluetoothMessageReceiver receiver;
    private BluetoothAdapter mBluetoothAdapter = null;
    private BluetoothChatService mChatService = null;



	// onCreate 가 실행된 이후에 자동으로 연결하도록 예약한다.
	public void set_auto_connect_receiver(BluetoothMessageReceiver receiver)
	{
		auto_connect = true;
		this.receiver = receiver;
	}


    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        // Get local Bluetooth adapter
        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        // If the adapter is null, then Bluetooth is not supported
        if (mBluetoothAdapter == null)
        {
            FragmentActivity activity = getActivity();
            Toast.makeText(activity, "Bluetooth is not available", Toast.LENGTH_LONG).show();
            activity.finish();
        }
	    else if (auto_connect)
        {
	        connect();
        }
    }

    public void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        // When the request to enable Bluetooth returns
        if (resultCode == Activity.RESULT_OK)
        {
            // Bluetooth is now enabled, so set up a chat session
            mChatService = new BluetoothChatService(getActivity(), mHandler);
        }
        else
        {
            // User did not enable Bluetooth or an error occurred
            // Log.d(TAG, "BT not enabled");
            Toast.makeText(getActivity(), R.string.not_connected, Toast.LENGTH_SHORT).show();
        }
    }


    private final Handler mHandler = new Handler()
    {
        @Override
        public void handleMessage(Message msg)
        {
            FragmentActivity activity = getActivity();
            switch (msg.what)
            {
                case Constants.MESSAGE_READ:
                    byte[] readBuf = (byte[]) msg.obj;
                    // construct a string from the valid bytes in the buffer
                    String readMessage = new String(readBuf, 0, msg.arg1);
                    receiver.use_received_message(readMessage);
                    break;

                // unable to connect device 같은 메세지를 출력한다.
                case Constants.MESSAGE_TOAST:
                    if (null != activity)
                    {
                        Toast.makeText(activity, msg.getData().getString(Constants.TOAST),
                                Toast.LENGTH_SHORT).show();
                    }
                    break;
            }
        }
    };


    @Override
    public void onDestroy()
    {
        super.onDestroy();
        if (mChatService != null)
        {
            mChatService.stop();
        }
    }

    @Override
    public void onResume()
    {
        super.onResume();

        // Performing this check in onResume() covers the case in which BT was
        // not enabled during onStart(), so we were paused to enable it...
        // onResume() will be called when ACTION_REQUEST_ENABLE activity returns.
        if (mChatService != null)
        {
            // Only if the state is STATE_NONE, do we know that we haven't started already
            if (mChatService.getState() == BluetoothChatService.STATE_NONE)
            {
                // Start the Bluetooth chat services
                mChatService.start();
            }
        }
    }


    public void connect_and_set_receiver(BluetoothMessageReceiver receiver)
    {
        // If BT is not on, request that it be enabled.
        // setupChat() will then be called during onActivityResult
        if (!mBluetoothAdapter.isEnabled())
        {
            Intent enableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableIntent, 0);
            /*
            위에 두 줄을 실행하면, 블루투스를 켤지 물어보고,
            아레에 있는 onActivityResult 메서드를 실행해서,
            OK 와 CANCEL 중 어느 버튼을 눌렀는가에 따라서 동작을 한다.
             */
        }
        else // 여기서 추가적인 준비동작을 한다.
        {
            connect();
	        this.receiver = receiver;
        }
    }


    private void connect()
    {
        Toast.makeText(getActivity(), "연결", Toast.LENGTH_SHORT).show();
        // Get the BluetoothDevice object
        BluetoothDevice device = mBluetoothAdapter.getRemoteDevice(DESTINATION_ADDRESS);
        mChatService = new BluetoothChatService(getActivity(), mHandler);
        mChatService.connect(device, false);
    }

    public void disconnect()
    {
        Toast.makeText(getActivity(), "연결해제", Toast.LENGTH_SHORT).show();
        mChatService.start();
    }

    public void send(String message)
    {
        Toast.makeText(getActivity(), "보내기: " + message, Toast.LENGTH_SHORT).show();


        // Check that we're actually connected before trying anything
        if (mChatService.getState() != BluetoothChatService.STATE_CONNECTED)
        {
            Toast.makeText(getActivity(), R.string.not_connected, Toast.LENGTH_SHORT).show();
            return;
        }

        // Check that there's actually something to send
        if (message.length() > 0)
        {
            // Get the message bytes and tell the BluetoothChatService to write
            byte[] send = message.getBytes();
            mChatService.write(send);
        }
    }

}
