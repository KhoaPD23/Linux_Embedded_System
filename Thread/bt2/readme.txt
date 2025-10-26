Tại sao cần sử dụng mutex trong bài toán này?
- Đảm bảo tính đúng đắn (synchronization): Khi một luồng đang tăng counter, các luồng khác phải chờ để tránh xung đột dữ liệu.
- Tránh điều kiện tranh chấp (race condition): Nếu nhiều luồng cùng đọc và ghi counter mà không có mutex, giá trị có thể bị ghi đè sai.
- Đảm bảo kết quả cuối cùng chính xác: Mỗi luồng tăng đúng 1000000 lần → tổng cộng phải là 3000000. Mutex giúp đảm bảo mỗi lần tăng là an toàn và không bị mất dữ liệu.

Điều gì xảy ra nếu bỏ qua mutex?
- Race condition xảy ra: Các luồng có thể đọc cùng một giá trị của counter, rồi cùng tăng và ghi lại → mất lượt tăng.
- Kết quả cuối cùng không ổn định: Có thể nhỏ hơn 3000000. Mỗi lần chạy chương trình có thể ra kết quả khác nhau do thứ tự thực thi luồng không xác định.

