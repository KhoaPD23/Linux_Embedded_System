Nếu không gọi lại alarm(1) trong hàm xử lý SIGALRM thì:
- Chương trình chỉ nhận SIGALRM một lần duy nhất.
- Bộ đếm không tiếp tục tăng, vì không có tín hiệu nào được gửi sau lần đầu.
- Chương trình sẽ treo ở pause() mãi mãi, không thoát.