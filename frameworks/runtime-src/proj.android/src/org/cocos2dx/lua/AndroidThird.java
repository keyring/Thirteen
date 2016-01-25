package org.cocos2dx.lua;

import android.app.Activity;
import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxLuaJavaBridge;

import android.os.Bundle;
import android.widget.Toast;

import com.tencent.connect.share.QQShare;
import com.tencent.tauth.IUiListener;
import com.tencent.tauth.Tencent;
import com.tencent.tauth.UiError;

public class AndroidThird {

	private static Cocos2dxActivity mainActivity = null;
	private static Tencent mTencent;
	public static void init(Cocos2dxActivity activity) {
		mainActivity = activity;
        if (mTencent == null) {
            mTencent = Tencent.createInstance("1105123024", activity);
        }
	}

    private static void shareToQQ(String title, String summary, String target_url, String image_url, String appname){
        final String tit = title;
        final String sum = summary;
        final String tar = target_url;
        final String img = image_url;
        final String app = appname;

        Runnable runnable = new Runnable(){
    		@Override
			public void run() {
		        final Bundle params = new Bundle();
		        params.putInt(QQShare.SHARE_TO_QQ_KEY_TYPE, QQShare.SHARE_TO_QQ_TYPE_DEFAULT);
		        params.putString(QQShare.SHARE_TO_QQ_TITLE, tit);
		        params.putString(QQShare.SHARE_TO_QQ_SUMMARY,  sum);
		        params.putString(QQShare.SHARE_TO_QQ_TARGET_URL,  tar);
		        params.putString(QQShare.SHARE_TO_QQ_IMAGE_URL,img);
		        params.putString(QQShare.SHARE_TO_QQ_APP_NAME,  app);
		        // params.putInt(QQShare.SHARE_TO_QQ_EXT_INT,  QQShare.SHARE_TO_QQ_FLAG_QZONE_AUTO_OPEN);   
		        // Toast.makeText(AndroidThird.mainActivity, "登录失败", Toast.LENGTH_LONG).show();   
		        mTencent.shareToQQ(AndroidThird.mainActivity, params, new IUiListener() {
		            @Override
		            public void onCancel() {
		                // if (shareType != QQShare.SHARE_TO_QQ_TYPE_IMAGE) {
		                //     Util.toastMessage(QQShareActivity.this, "onCancel: ");
		                // }
		            }
		            @Override
		            public void onComplete(Object response) {
		                // TODO Auto-generated method stub
		                // Util.toastMessage(QQShareActivity.this, "onComplete: " + response.toString());
		            }
		            @Override
		            public void onError(UiError e) {
		                // TODO Auto-generated method stub
		                // Util.toastMessage(QQShareActivity.this, "onError: " + e.errorMessage, "e");
		            }
		        });

			}
    	};

    	mainActivity.runOnUiThread(runnable);


    }

}