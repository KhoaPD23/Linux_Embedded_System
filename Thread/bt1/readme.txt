* pthread_create()
	Vai trò: Tạo một luồng mới trong chương trình.
	Cú pháp: int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
	Tham số:
		thread: Con trỏ đến biến kiểu pthread_t — nơi lưu ID của luồng mới.
		attr: Thuộc tính của luồng (có thể là NULL để dùng mặc định).
		start_routine: Hàm sẽ được thực thi bởi luồng mới (phải có kiểu void* và nhận void* làm tham số).
		arg: Tham số truyền vào cho hàm start_routine.
		
* pthread_join()
	Vai trò: Đợi một luồng kết thúc trước khi tiếp tục thực thi chương trình.
	Cú pháp: int pthread_join(pthread_t thread, void **retval);
	Tham số:
		thread: ID của luồng cần đợi (đã được tạo bằng pthread_create()).
		retval: Con trỏ tới biến sẽ nhận giá trị trả về từ luồng (có thể là NULL nếu không cần lấy giá trị).
	Giá trị trả về:
		0 nếu thành công.
		Khác 0 nếu có lỗi (ví dụ: luồng không tồn tại hoặc đã bị detach).
		
		
* Một luồng có thể kết thúc theo 3 cách chính:
	Hàm start_routine kết thúc bằng return:
		Luồng tự động kết thúc và giá trị trả về sẽ được truyền qua pthread_join().
		
	Gọi pthread_exit():
		Luồng kết thúc ngay lập tức và có thể truyền giá trị trả về.

	Bị hủy bởi luồng khác thông qua pthread_cancel():
		Nếu luồng đang ở trạng thái cho phép hủy (cancelable), nó sẽ kết thúc với giá trị PTHREAD_CANCELED.
