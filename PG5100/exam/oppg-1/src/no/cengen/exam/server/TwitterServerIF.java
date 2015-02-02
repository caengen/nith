package no.cengen.exam.server;

import no.cengen.exam.client.TwitterClientIF;
import no.cengen.exam.model.Tweet;

import java.rmi.Remote;
import java.rmi.RemoteException;

/**
 * User: Cengen
 * Date: 02/12/13
 * Time: 13:03
 */
public interface TwitterServerIF extends Remote {
    void registerTwitterClient(TwitterClientIF twitterClient) throws RemoteException;
    void broadcastTweet(Tweet tweet) throws RemoteException;
    void removeTwitterClient(TwitterClientIF twitterClient) throws RemoteException;
}
