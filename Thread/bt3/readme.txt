* Tại sao cần phải sử dụng mutex trong bài toán này?
	- Bảo vệ dữ liệu dùng chung (data và data_ready): Cả hai luồng đều truy cập và thay đổi các biến toàn cục. Nếu không có mutex, hai luồng có thể đọc/ghi cùng lúc, gây ra xung đột dữ liệu.
	- Đảm bảo tính nhất quán: Mutex giúp đảm bảo rằng chỉ một luồng được truy cập vào vùng dữ liệu tại một thời điểm. Tránh trường hợp Consumer đọc dữ liệu khi Producer chưa ghi xong.
	
* Điều gì xảy ra nếu không dùng mutex?
	- Race condition (tranh chấp dữ liệu): Producer có thể ghi vào data trong khi Consumer đang đọc → dữ liệu không chính xác. Consumer có thể đọc data_ready là 1 trước khi data thực sự được cập nhật.
