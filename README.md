## 尝试 ofono-vendor-qti-radio-plugin

## 依赖项目
1. git clone https://github.com/mer-hybris/ofono-binder-plugin -b upgrade-4.4.0
2. git clone https://github.com/sailfishos/ofono -b upgrade-4.4.0
3. git clone https://github.com/mer-hybris/libgbinder-radio -b upgrade-4.4.0
   
## 资料
1. glib 继承实现
2. G_DEFINE_TYPE用法 https://www.codenong.com/cs106693497/  
3. G_DEFINE_TYPE用法 https://blog.csdn.net/evsqiezi/article/details/83049655
4. g_type_register_static_simple(type, "A", sizeof(A_class), A_class_init, sizeof(A), A_init, 0LL);


## https://docs.sailfishos.org/Reference/Architecture/
| Area | Call chain | Notes |
| --- | --- | --- |
| Modem | [oFono](https://github.com/sailfishos/ofono)([ril driver](https://github.com/sailfishos/ofono/tree/master/ofono/drivers/ril)) <> [libgrilio](https://github.com/sailfishos/libgrilio) <> [ofono-ril-binder-plugin](https://github.com/mer-hybris/ofono-ril-binder-plugin) <> [libgbinder-radio](https://github.com/mer-hybris/libgbinder-radio) <> [libgbinder](https://github.com/mer-hybris/libgbinder) <> Android BSP HAL: android.hardware.radio | Android BSP >= 8 |
|  | [oFono](https://github.com/sailfishos/ofono)([ril driver](https://github.com/sailfishos/ofono/tree/master/ofono/drivers/ril)) <> [libgrilio](https://github.com/sailfishos/libgrilio) <> socket <> Android BSP: rild | Android BSP <= 7 |
|  | [oFono](https://github.com/sailfishos/ofono)<> [ofono-binder-plugin](https://github.com/mer-hybris/ofono-binder-plugin) <> ofono-vendor-qti-radio-plugin(未开源) <> [libgbinder-radio](https://github.com/mer-hybris/libgbinder-radio) <> [libgbinder](https://github.com/mer-hybris/libgbinder) <> Android BSP HAL: android.hardware.radio | for VoLTE |