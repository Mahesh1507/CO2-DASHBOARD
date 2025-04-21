# CO₂ Monitoring Dashboard

A real-time dashboard for monitoring CO₂ levels with WebSocket updates and CSV export functionality.

## Features

- Real-time CO₂ level monitoring
- Visual status indicators
- Historical data logging
- CSV export functionality
- Responsive design

## Prerequisites

- Node.js (v14 or higher)
- npm (Node Package Manager)
- Access to a Node-RED instance running the CO₂ monitoring flow

## Installation

1. Clone this repository or download the files
2. Install dependencies:
   ```bash
   npm install
   ```

## Configuration

1. Update the Node-RED WebSocket URL in `server.js` if your Node-RED instance is running on a different address:
   ```javascript
   const nodeRedWs = new WebSocket('ws://your-node-red-ip:1880/ws/co2');
   ```

2. Update the CSV download endpoint URL in `server.js` if needed:
   ```javascript
   const response = await fetch('http://your-node-red-ip:1880/download-co2');
   ```

## Running the Server

1. Start the server:
   ```bash
   npm start
   ```

2. The dashboard will be available at:
   - Local: http://localhost:3000
   - Network: http://your-ip-address:3000

## Deployment Options

### Option 1: Deploy to a VPS/Cloud Server

1. Set up a server with Node.js installed
2. Copy the files to your server
3. Install dependencies
4. Start the server
5. Configure your domain to point to the server
6. Set up SSL using Let's Encrypt

### Option 2: Deploy to a PaaS (Platform as a Service)

1. Choose a PaaS provider (Heroku, DigitalOcean App Platform, etc.)
2. Connect your repository
3. Set environment variables if needed
4. Deploy the application

### Option 3: Deploy using Docker

1. Create a Dockerfile:
   ```dockerfile
   FROM node:16
   WORKDIR /app
   COPY package*.json ./
   RUN npm install
   COPY . .
   EXPOSE 3000
   CMD ["npm", "start"]
   ```

2. Build and run the Docker container:
   ```bash
   docker build -t co2-dashboard .
   docker run -p 3000:3000 co2-dashboard
   ```

## Security Considerations

1. Enable HTTPS in production
2. Set up proper CORS configuration
3. Implement rate limiting
4. Add authentication if needed
5. Keep dependencies updated

## Troubleshooting

1. Check Node-RED connection:
   - Ensure Node-RED is running
   - Verify WebSocket endpoint is correct
   - Check network connectivity

2. CSV download issues:
   - Verify Node-RED endpoint is accessible
   - Check server logs for errors
   - Ensure proper permissions

## License

MIT License 