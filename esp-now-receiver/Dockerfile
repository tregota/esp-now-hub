FROM python:3.12-slim

WORKDIR /app

# Copy data for add-on
COPY src/ ./
RUN pip install -r requirements.txt --break-system-packages

CMD ["python3", "esp-now-receiver.py"]