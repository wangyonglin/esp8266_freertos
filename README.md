-  IO14 输出高低电平 默认低电平
-  IO 5 长短触发事件
-  IO 02 UART1

- ESP8266 烧写地址
```

bootloader.bin              0x0 
app.bin                     0x10000 
partitions_singleapp.bin    0x8000
```

```
{
    "success":true,
    "result":{
        "trun":"on"    
    }
}

{
	"success":true,
	"result":{
		"trun":"off"
	}
}

{
	"success":true,
	"result":{
		"rf433":"FD0301010160DF"
	}
}

{
	"success":true,
	"result":{
		"rf433":"FD0301010260DF"
	}
}
```

 objMessageInit(&message);
        bzero(topic, sizeof(char) * 256);
        strncpy(topic, event->topic, event->topic_len);
        if (strcmp(topic, TOPIC_TRUN) == 0)
        {
            if (objMessageTrun(event->data, &message) == ESP_OK)
            {
                if (xQueueSend(queue->xQueue, &message, NULL) != pdPASS)
                {
                    ESP_LOGI(TAG, "objMessageTrun Fail");
                }
            }
        }
        else if (strcmp(topic, TOPIC_RF433) == 0)
        {
            if (objMessageRF433(event->data, &message) == ESP_OK)
            {
                if (xQueueSend(queue->xQueue, &message, NULL) != pdPASS)
                {
                    ESP_LOGI(TAG, "objMessageRF433 Fail");
                }
            }
        }
        objMessageClean(&message);